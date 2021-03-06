# Ignition Rendering: Rendering library for robot applications

**Maintainer:** ichen [AT] openrobotics [DOT] org

[![GitHub open issues](https://img.shields.io/github/issues-raw/ignitionrobotics/ign-rendering.svg)](https://github.com/ignitionrobotics/ign-rendering/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/ignitionrobotics/ign-rendering.svg)](https://github.com/ignitionrobotics/ign-rendering/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/ignitionrobotics/ign-rendering/branch/master/graph/badge.svg)](https://codecov.io/gh/ignitionrobotics/ign-rendering/branch/default)
Ubuntu Xenial | [![](https://build.osrfoundation.org/buildStatus/icon?job=ignition_rendering-ci-master-xenial-amd64)](https://build.osrfoundation.org/job/ignition_rendering-ci-master-xenial-amd64/)
Ubuntu Bionic | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_rendering-ci-master-bionic-amd64)](https://build.osrfoundation.org/job/ignition_rendering-ci-master-bionic-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_rendering-ci-master-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_rendering-ci-master-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ign_rendering-ci-win)](https://build.osrfoundation.org/job/ign_rendering-ci-win)

Ignition Rendering is a C++ library designed to provide an abstraction
for different rendering engines. It offers unified APIs for creating
3D graphics applications.

Ignition Rendering is a component in the ignition framework, a set
of libraries designed to rapidly develop robot applications.

# Table of Contents

[Features](#features)

[Install](#install)

* [Binary Install](#binary-install)

* [Source Install](#source-install)

    * [Prerequisites](#prerequisites)

    * [Building from Source](#building-from-source)

[Usage](#usage)

[Documentation](#documentation)

[Testing](#testing)

[Folder Structure](#folder-structure)

[Code of Conduct](#code-of-conduct)

[Contributing](#code-of-contributing)

[Versioning](#versioning)

[License](#license)

# Features

* Support for rendering engines including OGRE and OptiX
* Plugin-based architecture. Mulitple rendering engine plugins can be loaded at run time.
* Object-oriented scene management.

# Install

We recommend following the [Binary Install](#binary-install) instructions to get up and running as quickly and painlessly as possible.

The [Source Install](#source-install) instructions should be used if you need the very latest software improvements, you need to modify the code, or you plan to make a contribution.

## Binary Install

Ignition Rendering's binary packages are still pre-releases and unstable.

On Ubuntu Bionic, it's possible to install Ignition Rendering's version 1 pre-releases as follows:

Add OSRF packages:

    sudo apt -y install wget lsb-release gnupg
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-prerelease `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-prerelease.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt update

Install Ignition Rendering:

    # This installs ign-rendering3. Change the number after libignition-rendering to the version you want
    sudo apt install libignition-rendering3-dev

## Source Install

### Prerequisites

#### Ubuntu Bionic 18.04 or above

Install dependencies:

    sudo apt -y install wget lsb-release gnupg
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-prerelease `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-prerelease.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt update
    sudo apt install -y \
        g++-8 \
        cmake \
        pkg-config \
        git \
        libglew-dev  \
        libfreeimage-dev \
        freeglut3-dev \
        libxmu-dev \
        libxi-dev \
        libignition-cmake2-dev \
        libignition-math6-dev \
        libignition-common3-dev \
        libignition-plugin-dev
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8 --slave /usr/bin/gcov gcov /usr/bin/gcov-8

Clone source code

    # This checks out the `default` branch. You can append `-b ign-rendering#` (replace # with a number) to checkout a specific version
    git clone http://github.com/ignitionrobotics/ign-rendering

#### Version 0 (Legacy version for Ubuntu Xenial 16.04 or above)

Install dependencies:

    sudo apt -y install wget lsb-release gnupg
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-prerelease `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-prerelease.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt update
    sudo apt install -y \
        cmake \
        pkg-config \
        git \
        libglew-dev  \
        libfreeimage-dev \
        freeglut3-dev \
        libxmu-dev \
        libxi-dev \
        libignition-cmake1-dev \
        libignition-math5-dev \
        libignition-common2-dev

Clone source code, note you'll need the `ign-rendering0` branch:

    git clone http://github.com/ignitionrobotics/ign-rendering -b ign-rendering0


#### Supported Rendering Engines

Ignition Rendering will look for rendering libraries installed in the system and
build the relevant plugins if dependencies are found.

**OGRE 1.x**

    # this installs ogre 1.9. Alternatively, you can install 1.8
    sudo apt-get install libogre-1.9-dev

**OGRE 2.x (supported in Versions >= ign-rendering1)**

Add OSRF packages if you have not done so already:

    sudo apt -y install wget lsb-release gnupg
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-prerelease `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-prerelease.list'
    wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    sudo apt update

Install OGRE 2.1 debs

    sudo apt install libogre-2.1-dev

**OptiX (experimental)**

Download and install by following instructions on NVIDIA website

CUDA:

http://docs.nvidia.com/cuda

OptiX:

https://developer.nvidia.com/optix

Update `LD_LIBRARY_PATH` and add an `OPTIX_INSTALL_DIR` environment variables
so that ign-rendering can find Optix, e.g. if you installed version 4.0.2 in HOME/optix:

    export LD_LIBRARY_PATH=${HOME}/optix/NVIDIA-OptiX-SDK-4.0.2-linux64/lib64:${LD_LIBRARY_PATH}
    export OPTIX_INSTALL_DIR=${HOME}/optix/NVIDIA-OptiX-SDK-4.0.2-linux64

Note: If you encounter errors about different exception specifiers in optix math
when building Ign Rendering OptiX plugin, edit
`[optix_install_dir]/include/optixu/optixu_math_namespace.h` and comment
out the section that defines `fminf`, fmaxf, and `copysignf` (for optix
sdk 4.0.2, comment out lines 167-206).


### Building from source

Build and install as follows:

    cd ign-rendering
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install/dir
    make -j4
    make install

Replace `/path/to/install/dir` to whatever directory you want to install this package to

# Usage

The Ign Rendering API can be found in the documentation. See the
[Documentation](#documentation) section on how to build the
documentation files using Doxygen.

You can also take a look at the sample applications in the `examples` folder.

# Documentation

API documentation can be generated using Doxygen

    sudo apt install -y doxygen

Build documentation

    cd build
    make doc

View documentation

    firefox doxygen/html/index.html

# Testing

Tests can be run by building the `test` target:

    cd build
    make test

To run tests specific to a render engine, set the `RENDER_ENGINE_VALUES` environment variable, e.g.

    RENDER_ENGINE_VALUES=ogre2 make test

# Folder Structure

* `include/ignition/rendering`: Contains all the public header files which will be installed

* `src`: Contains all the C++ source code which are not installed.

* `test`: All integration, performance and regression tests go here, under their
  specific folders.

* `examples`: Sample programs to demonstrate different features of ign-rendering

* `doc`: Files used by Doxygen when generating documentation.

Rendering engine plugin implementation code is stored in their own folders

* `ogre` : OGRE 1.x rendering engine plugin

* `ogre2` : OGRE 2.x rendering engine plugin (available in versions >= ign-rendering1)

* `optix` : OptiX rendering engine plugin

# Contributing

Please see
[CONTRIBUTING.md](https://ignitionrobotics.org/docs/all/contributing).

# Code of Conduct

Please see
[CODE_OF_CONDUCT.md](https://github.com/ignitionrobotics/ign-gazebo/blob/master/CODE_OF_CONDUCT.md).

# Versioning

This library uses [Semantic Versioning](https://semver.org/). Additionally, this library is part of the [Ignition Robotics project](https://ignitionrobotics.org) which periodically releases a versioned set of compatible and complimentary libraries. See the [Ignition Robotics website](https://ignitionrobotics.org) for version and release information.

# License

This library is licensed under [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0). See also the [LICENSE](https://github.com/ignitionrobotics/ign-rendering/blob/master/LICENSE) file.
