#if defined _INC_players_count_inc
	#endinput
#endif
#define _INC_players_count_inc

#include <a_samp>

#define SAMP_LOGGER_COMPAT
#tryinclude <logger>
#tryinclude <progress2>
#tryinclude <YSI_Coding\y_hooks>

const
    PC_DEFAULT_BAR_COLOUR        =			-16777046,
    Float: PC_DEFAULT_BAR_VALUE  =			1000.0000;

// * Variables *
static
	gPlayersConnected = 0,

	PlayerText: PC_TextDrawCount[MAX_PLAYERS] = {PlayerText: INVALID_TEXT_DRAW, ...},
	PlayerBar: PC_ProgressBar[MAX_PLAYERS] = {INVALID_PLAYER_BAR_ID, ...};

// * API *
static
	bool: PC_Status[MAX_PLAYERS],

	PC_BarColour[MAX_PLAYERS];

// * Hooks *
public OnPlayerConnect(playerid)
{
	++gPlayersConnected;

	PC_CreatePlayerHud(playerid);

	#if defined PC_OnPlayerConnect
		return PC_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	--gPlayersConnected;

	PC_CreatePlayerHud(playerid, false);

	#if defined PC_OnPlayerDisconnect
		return PC_OnPlayerDisconnect(playerid);
	#else
		return 1;
	#endif
}

// * Functions *
stock PC_CreatePlayerHud(const playerid, bool: status = true)
{
	if (!status) {
		PlayerTextDrawDestroy(playerid, PC_TextDrawCount[playerid]);
		DestroyPlayerProgressBar(playerid, PC_ProgressBar[playerid]);

		PC_UpdateBarTD(playerid);

		PC_Status[playerid] = false;

		return 1;
	}

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

	PC_ProgressBar[playerid] = CreatePlayerProgressBar(playerid, 429.000000, 436.000000, 194.000000, 0.200000, PC_DEFAULT_BAR_COLOUR, PC_DEFAULT_BAR_VALUE, 0);

	PlayerTextDrawShow(playerid, PC_TextDrawCount[playerid]);
	ShowPlayerProgressBar(playerid, PC_ProgressBar[playerid]);
	SetPlayerProgressBarValue(playerid, PC_ProgressBar[playerid], PC_DEFAULT_BAR_VALUE);

	PC_UpdateBarTD(playerid);

	PC_Status[playerid] = true;

	return 1;
}

stock PC_SetPlayerBarColour(const playerid, const colour = PC_DEFAULT_BAR_COLOUR)
{
	PC_BarColour[playerid] = colour;

	SetPlayerProgressBarColour(playerid, PC_ProgressBar[playerid], PC_BarColour[playerid]);
	ShowPlayerProgressBar(playerid, PC_ProgressBar[playerid]);

	return 1;
}

stock bool: PC_GetPlayerHudStatus(const playerid)
{
	return PC_Status[playerid];
}

stock PC_GetPlayerBarColor(const playerid)
{
	return PC_BarColour[playerid];
}

stock PC_UpdateBarTD(const playerid)
{
	static
		pc_string[30];


	format(
		pc_string, sizeof pc_string, "~y~PLAYERS:_~w~%d/~r~%d",
		gPlayersConnected, MAX_PLAYERS
	);

	PlayerTextDrawSetString(playerid, PC_TextDrawCount[playerid], pc_string);
	SetPlayerProgressBarValue(playerid, PC_ProgressBar[playerid], (gPlayersConnected + 5.0));

	return 1;
}

// * ALS *
// OnPlayerConnect
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect PC_OnPlayerConnect
#if defined PC_OnPlayerConnect
	forward PC_OnPlayerConnect(playerid);
#endif

// OnPlayerDisconnect
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect PC_OnPlayerDisconnect
#if defined PC_OnPlayerDisconnect
	forward PC_OnPlayerDisconnect(playerid);
#endif