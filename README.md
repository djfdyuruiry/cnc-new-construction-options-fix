# 🛠 New Construction Options 🛠

C&C New Construction Options is a replacement game engine for  `Command & Conquer: Tiberian Dawn` & `Command & Conquer:Red Alert`. It's goals are to enhance the gameplay and modding experience.

This project aims to provide an out-of-the-box experience that looks and feels like the original games while giving users unprecedented control over customization and enhancements through in-game menus, INI file configuration and Lua scripting.

> This project is a fork of [Vanilla Conquer](https://github.com/TheAssemblyArmada/Vanilla-Conquer)

---

# ⚠&nbsp;&nbsp;&nbsp; Building... &nbsp;&nbsp;&nbsp;⚠

![Construction Yard Animation](docs/img/con-yard.gif)![Construction Yard Animation](docs/img/con-yard.gif)![Construction Yard Animation](docs/img/con-yard.gif)![Construction Yard Animation](docs/img/con-yard.gif)![Construction Yard Animation](docs/img/con-yard.gif)![Construction Yard Animation](docs/img/con-yard.gif)

> EVA: "NOT READY"

This project is under construction and intial development, so no release builds are available yet - I am working on refactoring and behind the scenes changes first.

> If you are brave and want to try a dev build, grab the latest binaries here: https://github.com/djfdyuruiry/cnc-new-construction-options/releases/tag/latest

---

### [> Planned Features](docs/planned-features)
### [> Enhancements List](docs/enhancements)

### [> Project Vision](#project-vision)
### [> Building](#building)
### [> Contributing](#contributing)
### [> Convential Commits](#convential-commits)
### [> License](#license)
### [> Why This Exists](#why)

## Project Vision

The main target will be a standalone `Tiberian Dawn` engine, with a view to move on to `Red Alert` when there are working enhancements to port from `Tiberian Dawn`.

Eventually I want to also want to support using this repo as a mod for C&C Remastered Collection as that is popular.

My vision for `Tiberian Dawn`:

- Users can customize their C&C experience without modifying C++ code
- Tweaks and enhancements are immerisive, they surface in game as UI menus
- Low level control is available for nearly all aspects of the game engine via config files
  - Anything currently stored in source code, binary files, hidden in MIX files etc. should be made available in plain text format
- Static limits imposed by the original source code are removed (no cap on Unit types, Music tracks etc.)
- Combine the best of old tools and engine changes to give modders the ability to make as many changes as possible
- Patches from `Vanilla Conquer` are synced in when possible

## Contributing

I am not actively seeking any contributions, but feature requests and any feedback are always welcome. Since I work on this project in my free time, please just record what you can on GitHub by raising issues and I will respond where I can.

## Building

If you are want to be brave and try building this yourself, please refer to the original Vanilla Conquer guide: [Vanilla Conquer GitHub](https://github.com/TheAssemblyArmada/Vanilla-Conquer/wiki/Compiling-Vanilla-Conquer)

Use the `nco-tiberian-dawn` cmake preset, like this: `cmake --workflow --preset nco-tiberian-dawn`

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
 - feat!: A feature which has breaking changes
 - fix: A bug fix
 - docs: Documentation changes
 - style: Changes that do not affect the meaning of the code (white-space, formatting, etc.)
 - refactor: Code changes that neither fix a bug nor add a feature
 - perf: Performance improvements
 - test: Adding or refactoring tests
 - chore: Other changes that don't modify src or test files

Examples
 - `feat(tiberian-dawn)!: make Kane die in SCG15`
 - `fix: correct normal difficulty credits for HUMVEE`

By following this convention, we maintain a clean and informative project history.

## License

This project is licensed under the GPLv3 license. See the [LICENSE](LICENSE) file for details.

## Why

I made a mod for the C&C Remastered Collection when it was released on Steam: [[TD] 🛠 NCO 🛠 (RULES.INI 📃 & Lua Scripting ⚙)](https://steamcommunity.com/sharedfiles/filedetails/?id=2147631402)

It changed Tiberian Dawn in the following ways:

- A great level of control over the game engine
- Brought `RULES.INI` for Tiberian Dawn up to the standard of Red Alert
- Added Lua scripting
- Merged in changes from popular Quality of Life mods and enhancements (A* path finding, unit rallying etc.)
  - _Whilst keeping them configurable and optional_
- Added enhancements to improve gameplay experience (Better skirmish AI)

--- 

Whilst this mod was a alot of fun I now want to achieve similar aims to projects like:

- TRX: github.com/LostArtefacts/TRX (Tomb Radier)
- R.E.L.I.V.E: https://github.com/AliveTeam/alive_reversing (Abe's Oddysee)

These took retro classics and reverse engineered and revamped them to work flawlessy on modern systems, adding a bunch of configurable enhancements as well.

Vanilla Conquer has done the hard work of making a cross-platform standlone game engine decoupled from the Remastered Collection. I will use this as a base to bring in the lessons of my NCO mod to make a similar project to TRX/R.E.L.I.V.E
