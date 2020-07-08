/*
  * Include: Players Count
  * Author: Emmett
  * Date: 8th July
  * Copyright (C) 2020
  */


#include <a_samp>

#define SAMP_LOGGER_COMPAT

#tryinclude <logger>
#tryinclude <progress2>
#tryinclude <YSI_Coding\y_hooks>


#define __PC_DEFAULT_BAR_COLOR			(-16777046)
#define __PC_DEFAULT_BAR_VALUE			(1000.0000)


/// <summary>
/// Variables
/// </summary>
static
	__pcPlayersConnected = 0,

	PlayerText: PC_TextDrawCount[MAX_PLAYERS],
	PlayerBar: PC_ProgressBar[MAX_PLAYERS] = {INVALID_PLAYER_BAR_ID,...};


/// <summary>
/// API
/// </summary>
static
	bool: __pcStatus[MAX_PLAYERS],

	__pcBarColor[MAX_PLAYERS];


/// <summary>
/// Hooks
/// </summary>
hook OnPlayerConnect(playerid)
{
	++__pcPlayersConnected;

	PC_CreatePlayerHud(playerid, true);

	return 1;
}


hook OnPlayerDisconnect(playerid, reason)
{
	--__pcPlayersConnected;

	PC_CreatePlayerHud(playerid, false);

	return 1;
}


/// <summary>
/// Functions
/// </summary>
stock PC_CreatePlayerHud(const playerid, bool: __status)
{
	if (!__status)
	{
		PlayerTextDrawDestroy(playerid, PC_TextDrawCount[playerid]);
		DestroyPlayerProgressBar(playerid, PC_ProgressBar[playerid]);

		PC_UpdateBarTD(playerid);

		__pcStatus[playerid] = false;

		return 1;
	}

	/// <summary>
	/// Player textdraw
	/// </summary>
	PC_TextDrawCount[playerid] 			= CreatePlayerTextDraw(playerid, 521.200073, 421.066680, "~y~PLAYERS:_~w~1000/~r~1000");
	PlayerTextDrawLetterSize 			(playerid, PC_TextDrawCount[playerid], 0.237599, 0.771200);
	PlayerTextDrawAlignment 			(playerid, PC_TextDrawCount[playerid], 2);
	PlayerTextDrawColor  				(playerid, PC_TextDrawCount[playerid], -1);
	PlayerTextDrawSetShadow  			(playerid, PC_TextDrawCount[playerid], 0);
	PlayerTextDrawSetOutline 			(playerid, PC_TextDrawCount[playerid], 1);
	PlayerTextDrawBackgroundColor 		(playerid, PC_TextDrawCount[playerid], 255);
	PlayerTextDrawFont 					(playerid, PC_TextDrawCount[playerid], 1);
	PlayerTextDrawSetProportional 		(playerid, PC_TextDrawCount[playerid], 1);
	PlayerTextDrawSetShadow 			(playerid, PC_TextDrawCount[playerid], 0);

	/// <summary>
	/// Player bar
	/// </summary>
	PC_ProgressBar[playerid] = CreatePlayerProgressBar(playerid, 429.000000, 436.000000, 194.000000, 0.200000, __PC_DEFAULT_BAR_COLOR, __PC_DEFAULT_BAR_VALUE, 0);

	PlayerTextDrawShow(playerid, PC_TextDrawCount[playerid]);
	ShowPlayerProgressBar(playerid, PC_ProgressBar[playerid]);
	SetPlayerProgressBarValue(playerid, PC_ProgressBar[playerid], __PC_DEFAULT_BAR_VALUE);

	PC_UpdateBarTD(playerid);

	__pcStatus[playerid] = true;

	return 1;
}


/// <summary>
/// Change player bar color
/// </summary>
stock PC_SetPlayerBarColor(const playerid, const color = __PC_DEFAULT_BAR_COLOR)
{
	__pcBarColor[playerid] = color;

	SetPlayerProgressBarColour(playerid, PC_ProgressBar[playerid], __pcBarColor[playerid]);
	ShowPlayerProgressBar(playerid, PC_ProgressBar[playerid]);

	return 1;
}


/// <summary>
/// Getting status of player hud
/// </summary>
stock bool: PC_GetPlayerHudStatus(const playerid)
{
	return __pcStatus[playerid];
}


/// <summary>
/// Getting player bar color
/// </summary>
stock PC_GetPlayerBarColor(const playerid)
{
	return __pcBarColor[playerid];
}


/// <summary>
/// Updating player bar & player textdraw status
/// </summary>
stock PC_UpdateBarTD(const playerid)
{
	static
		__string[30];


	format(
		__string, sizeof __string, "~y~PLAYERS:_~w~%d/~r~%d",
		__pcPlayersConnected, MAX_PLAYERS
	);

	PlayerTextDrawSetString(playerid, PC_TextDrawCount[playerid], __string);
	SetPlayerProgressBarValue(playerid, PC_ProgressBar[playerid], (__pcPlayersConnected + 5.0));

	return 1;
}
