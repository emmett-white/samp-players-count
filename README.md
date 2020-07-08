# samp-players-count

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl package install emmett-white/samp-players-count
```

Include in your code and begin using the library:

```pawn
#include <players-count>
```

## Functions

```pawn
stock PC_CreatePlayerHud(const playerid, bool: __status)

// Usage
// Example
YCMD:hud(playerid, const params[], help)
{
  PC_CreatePlayerHud(playerid, (PC_GetPlayerHudStatus(playerid) ? (false) : (true)));
  return COMMAND_OK;
}
```

```pawn
stock PC_SetPlayerBarColor(const playerid, const color = __PC_DEFAULT_BAR_COLOR)

// Usage
// Example
YCMD:barcolor(playerid, const params[], help)
{
    static
        __color;


    if (sscanf(params, "x", __color))
        return SendClientMessage(playerid, -1, "/barcolor [hex color]");


    PC_SetPlayerBarColor(playerid, __color);

    return COMMAND_OK;
}
```

```pawn
stock bool: PC_GetPlayerHudStatus(const playerid)
stock PC_GetPlayerBarColor(const playerid)
stock PC_UpdateBarTD(const playerid)
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```

## Images
![Image](https://i.ibb.co/VtnrFCj/sa-mp-838.png)
![Image](https://i.ibb.co/9VWxHHY/sa-mp-839.png)
