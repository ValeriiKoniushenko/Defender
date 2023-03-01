// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Multiplayer/MainGameSession.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainGameSession, All, All);

void AMainGameSession::RegisterServer()
{
	Super::RegisterServer();
}

void AMainGameSession::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName InSessionName,
                                   int32 MaxPublicConnections/* = 4*/, bool bIsLan/* = false*/)
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(
		this, &ThisClass::OnCreateSessionCompete);

	if (!UserId.IsValid())
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Was passed invalid user id"));
		return;
	}

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSubsystem"));
		return;
	}

	OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!OnlineSessionInterface.IsValid())
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSessionInterface"));
		return;
	}

	FNamedOnlineSession* ExistingSession = OnlineSessionInterface->GetNamedSession(InSessionName);
	if (ExistingSession)
	{
		UE_LOG(LogMainGameSession, Display, TEXT("Such session already exists, it will be deleted"));
		OnlineSessionInterface->DestroySession(InSessionName);
	}
	
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

	SessionSettings = MakeShareable(new FOnlineSessionSettings);
	SessionSettings->bIsLANMatch = bIsLan;
	SessionSettings->NumPublicConnections = MaxPublicConnections;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"),
	                     EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	OnlineSessionInterface->CreateSession(*UserId, InSessionName, *SessionSettings);
}

void AMainGameSession::FindSessions(TSharedPtr<const FUniqueNetId> UserId, int32 MaxSearchResults/* = 10000*/,
                                    bool bIsLan/* = false*/)
{
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(
		this, &ThisClass::OnFindSessionsCompete);

	if (!OnlineSessionInterface.IsValid())
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (!OnlineSubsystem)
		{
			UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSubsystem"));
			return;
		}

		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		if (!OnlineSessionInterface.IsValid())
		{
			UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSessionInterface"));
			return;
		}
	}
	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
	
	OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch);
	OnlineSessionSearch->MaxSearchResults = MaxSearchResults;
	OnlineSessionSearch->bIsLanQuery = bIsLan;

	OnlineSessionInterface->FindSessions(*UserId, OnlineSessionSearch.ToSharedRef());
}

void AMainGameSession::JoinSession(FOnlineSessionSearchResult SessionData)
{
	OnJoinSessionsCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(
		this, &ThisClass::OnJoinSessionsCompete);

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSubsystem"));
		return;
	}

	OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!OnlineSessionInterface.IsValid())
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSessionInterface"));
		return;
	}

	OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionsCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionData);
}

void AMainGameSession::OnCreateSessionCompete(FName CurrentSessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogMainGameSession, Display, TEXT("Session '%s' was created"), *CurrentSessionName.ToString());
	}
	else
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Session '%s' was not created"), *CurrentSessionName.ToString());
	}
}

void AMainGameSession::OnFindSessionsCompete(bool bWasSuccessful)
{
	SearchResults.Empty();
	
	for (auto Result : OnlineSessionSearch->SearchResults)
	{
		FSearchResult SearchResult;
		SearchResult.Data = Result;
		SearchResult.Id = Result.GetSessionIdStr(); 
		SearchResult.Name = Result.Session.OwningUserName;
		Result.Session.SessionSettings.Get(FName("MatchType"), SearchResult.MatchType);
		SearchResults.Add(SearchResult);
	}

	OnFoundSessionResult.Broadcast(SearchResults);
}

void AMainGameSession::OnJoinSessionsCompete(FName Name, EOnJoinSessionCompleteResult::Type Type)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSubsystem"));
		return;
	}

	OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!OnlineSessionInterface.IsValid())
	{
		UE_LOG(LogMainGameSession, Error, TEXT("Can't get OnlineSessionInterface"));
		return;
	}

	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Connection string: %s"), *Address));

			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
}