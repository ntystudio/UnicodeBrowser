// SPDX-FileCopyrightText: 2025 NTY.studio
#pragma once

#include "CoreMinimal.h"

#include "Engine/DeveloperSettings.h"

#include "Styling/CoreStyle.h"

#include "UnicodeBrowserOptions.generated.h"

class UFont;
struct FSlateFontInfo;
class UDataAsset_FontTags;

UCLASS(Config="Editor", DefaultConfig, meta = (DisplayName="Unicode Browser"))
class UNICODEBROWSER_API UUnicodeBrowserOptions : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(DisplayName="Preset")
	TObjectPtr<UDataAsset_FontTags> Preset;

	UPROPERTY(Config, EditAnywhere, meta=(UIMin=0))
	int32 GridCellPadding = 5;

	// allow to toggle the right side panel on/off
	UPROPERTY(Config, EditAnywhere)
	bool bShowSidePanel = true;

	// Show Characters which can't be displayed by the font
	UPROPERTY(Config, EditAnywhere)
	bool bShowMissing = false;

	// Show Characters which have a measurement of 0x0 (primary for debug purposes)
	UPROPERTY(Config, EditAnywhere)
	bool bShowZeroSize = false;

	// Cache the Character meta information while loading the font, this is slower while changing fonts, but may reduce delay for displaying character previews
	UPROPERTY(Config, EditAnywhere)
	bool bCacheCharacterMetaOnLoad = false;

	// pick Unicode range based on what's available in the font
	UPROPERTY(Config, EditAnywhere)
	bool bAutoSetRangeOnFontChange = false;

	UPROPERTY(Config, EditAnywhere)
	bool bSearch_AutoSetRange = true;

	UPROPERTY(Config, EditAnywhere)
	bool bSearch_CaseSensitive = false;

	UPROPERTY(Config, EditAnywhere)
	bool bRangeSelector_HideEmptyRanges = false;

	FSlateFontInfo& GetFontInfo();

	void SetFontInfo(FSlateFontInfo const& FontInfoIn);

	DECLARE_MULTICAST_DELEGATE(FOnUbOptionsChangedDelegate);
	FOnUbOptionsChangedDelegate OnFontChanged;

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	static UUnicodeBrowserOptions* Get();

private:
	UPROPERTY(Transient, DisplayName="Font")
	FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Regular", 18);

	UPROPERTY(Transient, DisplayName="Font")
	TObjectPtr<UFont const> Font = nullptr;

	UPROPERTY(Transient, DisplayName="FontTypeface", meta=(EditCondition="Font", GetOptions=GetTypeFaces))
	FName FontTypeFace = NAME_None;

	UFUNCTION()
	TArray<FString> GetTypeFaces() const;
};
