// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MainGameSession.generated.h"

USTRUCT()
struct FSearchResult
{
	GENERATED_BODY()
public:
	FString Id;
	FString Name;
	FString MatchType;
	FOnlineSessionSearchResult Data;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoundSessionResult, TArray<FSearchResult>, SearchResults);

/**
 * 
 */
UCLASS()
class DEFENDER_API AMainGameSession : public AGameSession
{
	GENERATED_BODY()
public:
	virtual void RegisterServer() override;
	void HostSession(TSharedPtr<const FUniqueNetId> UserId, FName InSessionName, int32 MaxPublicConnections = 4, bool bIsLan = false);
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, int32 MaxSearchResults = 10000, bool bIsLan = false);
	void JoinSession(FOnlineSessionSearchResult SessionData);

	FOnFoundSessionResult OnFoundSessionResult;
	
private:
	void OnCreateSessionCompete(FName CurrentSessionName, bool bWasSuccessful);
	void OnFindSessionsCompete(bool bWasSuccessful);
	void OnJoinSessionsCompete(FName Name, EOnJoinSessionCompleteResult::Type Type);

private:
	TArray<FSearchResult> SearchResults;
	IOnlineSessionPtr OnlineSessionInterface;
	
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionsCompleteDelegate;
	
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
};
