# Setting up WSL 2 (Windows Subsystem Linux) for CLion

## WSL installation

Run Windows PowerShell with administrator privileges and run these commands

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

**Restart** your machine to complete the WSL install and update to WSL 2.

Download and install [WSL 2](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

Run Windows PowerShell with administrator privileges again and run these commands

```powershell
wsl --set-default-version 2

Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
```

Download and install [Ubuntu](https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6?activetab=pivot:overviewtab) from
Microsoft Store

Run ubuntu, set up user and password and WSL 2 is installed

Now you can [install Docker](https://docs.docker.com/desktop/windows/install/) and run the `docker-compose.yml` by
running `docker-compose up` in this folder, or you can continue the instruction to set up
CLion to work with wsl

## Installing dependencies

You can see your disks in the `/mnt` folder in WSL
for example to access the `C:\Users\user\Documents\GitHub\laba1-sem3\laba` folder
you need to write this path: `/mnt/c/Users/user/Documents/GitHub/laba1-sem3/laba`



To install all linux packets simply run the `setup_wsl.sh` script by running in my case

```bash
cd /mnt/c/Users/user/Documents/GitHub/laba1-sem3/laba
./setup_wsl
```

It will download all needed packages.

## Setting up CLion toolchains

1. In CLion, go to **Settings / Preferences | Build, Execution, Deployment | Toolchains**.

2. Click plus icon to create a new toolchain and select **WSL**.

3. In the **Environment** field, select one of the available WSL distributions.
The list includes the distributions detected by `wsl.exe --list`, which includes the imported ones.

![Beautiful image](https://resources.jetbrains.com/help/img/idea/2021.2/cl_wsl_new_toolchain.png)

That's all, CLion automatically will handle connection to WSL and file management


## Used materials

1. CLion WSL setup guide - https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html

2. Windows WSL 2 setup guide - https://docs.microsoft.com/en-Us/windows/wsl/install-win10#set-a-distro-to-be-backed-by-wsl-2-using-the-command-line
