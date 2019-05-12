


# PFS_HDD_Manager

"PHM" is a single tool to handle all the needs of a PS2 internal Hard Drive user. It uses HDL_Dump and PFSShell Functions integrated in a sigle GUI meant to handle PS2 Hard Drives, managing Partitions, files and VMC`s
It is a ongoing project and still have lots of things to be implemented.
For now you can handle your PS2 HDD, Editing its partitions and folders... Some coding was made wrong and the function to transfer files from your PC to the HDD is not working properly, But soon it will

## Getting Started

For Compiling the project, download it`s zip and open with visual studio (working on 2017 and 2019 editions) - All settings are already done. You just need to compile it after checking pre-requisites

### Prerequisites

You will need to have installed:
- Visual Studio with:
-- c++ desktop dev kit
-- latest windows 10 SDK
-- latest VC++ tools

### Installing

after compilling the file, you have to get the folder "shell" and "ICONS" to the same folder that the .exe file will be

## Running the tests

For testing the software, you gonna need a Hard Drive or a virtual drive that can be formated.
If selected a device in the right drop doen list, you are gona be prompted to format it OR the device partitions are gonna be listed
After connecting the device to your PC and startting the software with admin rights, cligk the Debug button. Then the text box bellow should be filled with system HDD`s list and the ps2 hdd partition list

### Break down into end to end tests

This test shows if the .exe`s for HDL_Dump and PFSShell.exe are ok and if this is being started with the correct permissions.

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

* **Orley Eduardo (Leyed)** - *development of the project*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
Credits to UyJulian who mantain PFSShell sourcecode

PS2-HOME thread: http://www.ps2-home.com/forum/viewtopic.php?p=34567#p34567
