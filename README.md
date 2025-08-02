# 🛠 New Construction Options 🛠

C&C New Construction Options is a fork of [Vanilla Conquer](https://github.com/TheAssemblyArmada/Vanilla-Conquer) with goals to enhance the gameplay and modding experience for `Command & Conquer: Tiberian Dawn` & `Command & Conquer:Red Alert`. 

This project aims to provide an out-of-the-box experience faithful to the original games while giving users unprecedented control over customization and enhancements through in-game menus, INI file configuration and Lua scripting.

# ⚠&nbsp;&nbsp;&nbsp; Under Construction &nbsp;&nbsp;&nbsp;⚠

![Construction Yard Animation](docs/con-yard.gif)![Construction Yard Animation](docs/con-yard.gif)![Construction Yard Animation](docs/con-yard.gif)![Construction Yard Animation](docs/con-yard.gif)![Construction Yard Animation](docs/con-yard.gif)![Construction Yard Animation](docs/con-yard.gif)

There are no builds yet available for you to try - I am scoping out what this project will be.

As EVA would say: `NOT READY`

## Project Vision

The main target will be `Tiberian Dawn`, with a view to move on to `Red Alert` when there are working enhancements to port from `Tiberian Dawn`.

My vision for `Tiberian Dawn`:

- Users can customize their C&C experience without modifying C++ code
- Tweaks and enhancements are immerisive, they surface in game as UI menus
- Low level control is available for nearly all aspects of the game engine via config files
- Static limits imposed by the original source code are removed (no cap on Unit types, Music tracks etc.)
- Combine the best of old tools and engine changes to give modders the ability to make as many changes as possible
- Patches from `Vanilla Conquer` are synced in when possible

## Key Features (Planned)

- Configuration via INI files for easy customization (authentic C&C modding experience)
  - Option to use YAML files instead for modern comforts
- Event handling using Lua scripts
  - Slowly move select game logic out of the core engine
- New scripting APIs to access more game engine functionality
  - Ability to control scenario flow from Lua scripts, similar to OpenRA
- Simple mod loading system
  - Ability to replace files gradually and add new ones, similar to original MIX file logic
- Comprehensive documentation and tools for modders
  - Strong API documentation (Lua, INI, YAML etc.)
  - Good mocking tools to make testing complex scenarios and mods easy
- Attempt to keep compatbility where possible with original material
  - Old formats for maps, media files etc. should not have breaking changes
  - New functionality should replace or enhance old logic, in a opt-in manner

## Why and How

I originally published a mod for the C&C Remastered Collection when it was released on steam: [[TD] 🛠 NCO 🛠 (RULES.INI 📃 & Lua Scripting ⚙)](https://steamcommunity.com/sharedfiles/filedetails/?id=2147631402)

How it changed Tiberian Dawn:

- A great level of control over the game engine
- Brought `RULES.INI` for Tiberian Dawn up to the standard of Red Alert
- Added Lua scripting
- Merged in changes from popular Quality of Life mods and enhancements (A* path finding, unit rallying etc.)
  - _Whilst keeping them configurable and optional_
- Added enhancements to improve gameplay experience (Better skirmish AI)

---

Whilst this mod was a alot of fun and popular enough on Steam I really wanted to achieve similar aims to projects like:

- TRX: github.com/LostArtefacts/TRX
- R.E.L.I.V.E: https://github.com/AliveTeam/alive_reversing

These took retro classics and reverse engineered and revamped them to work flawlessy on modern systems, adding a bunch of configurable enhancements as well.

Vanilla Conquer has done the hard work of making a cross-platform standlone game engine decoupled from the Remastered Collection.

I will use this as a base to bring in the lessons of my NCO mod to make a similar project to TRX/R.E.L.I.V.E

## Contributing

I am not accepting any contributions right away, but feature requests and any feedback are always welcome.

I work on this project in my free time, so please just record what you can on GitHub and I will respond where I can.

## Building and Running Instructions

If you are want to be brave and try building this yourself, please refer to the original Vanilla Conquer repository: [Vanilla Conquer GitHub](https://github.com/TheAssemblyArmada/Vanilla-Conquer)

Use the `Tiberian Dawn (/w editor)` cmake preset.

## Convential Commits

Each commit message should The Conventional Commits specification:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

See: https://www.conventionalcommits.org/en/v1.0.0/#summary

Types:
 - feat: A new feature
 - fix: A bug fix
 - docs: Documentation changes
 - style: Changes that do not affect the meaning of the code (white-space, formatting, etc.)
 - refactor: Code changes that neither fix a bug nor add a feature
 - perf: Performance improvements
 - test: Adding or refactoring tests
 - chore: Other changes that don't modify src or test files

Examples
 - `feat: add hat wobble`
 - `fix: remove extra spaces on login screen`

By following this convention, we maintain a clean and informative project history.

## License

This project is licensed under the GPLv3 license. See the [LICENSE](LICENSE) file for details.
