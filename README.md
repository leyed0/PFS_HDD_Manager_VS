


# PFS_HDD_Manager

"PHM" is a tool meant to handle all the needs of a PS2 user who uses internal Hard Drives. Using HDL_Dump and PFSShell combined with a GUI the user can handle PS2 Hard Drives, managing Partitions, files and VMC`s

## Getting Started

For Compiling the project, download it`s zip and open with visual studio 2017 - All settings are already done. You just need to compile it after checking pre-requisites

### Prerequisites

You will need to have installed:
- c++ desktop dev kit
- latest windows 10 SDK
- latest VC++ tools

### Installing

after compilling the file, you have to get the folder shell to the same folder the .exe file will be

## Running the tests

For testing the software, you gonna need a ps2 formatted hdd with at least 1 partition.
After connecting the device to your PC and startting the software with admin rights, cligk the Debug button. Then the text box bellow should be filled with system HDD`s list and the ps2 hdd partition list

### Break down into end to end tests

This test shows if the .exe for HDL_Dumo is ok and if this is being started with the correct permissions.

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With


## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Orley Eduardo** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
Credits to UyJulian who mantain PFSShell sourcecode




In the GUI the user can install new games in his Device, edit already installed games, manage files in existing partitions (OPL is a good example), clone disk drives and manage his VMC`s (virtual Memory Cards), all in a intuitive way and without the worries or issues that the command-line system can give

The software idea has come after the creator(leyed) got very frustrated with the way things went when he tryed to install multiple games in his device and dump OPL images for his games and VMC files. No good option was found, with just a program tha needs a one-to-one file enterring through commandline or a old GUI that corrupt`s the entire hard drive.

Actually the program is ìn pre-development, with its initial structure being made.

PS2-HOME thread: http://www.ps2-home.com/forum/viewtopic.php?p=34567#p34567