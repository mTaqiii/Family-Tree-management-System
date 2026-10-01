# Family Tree Management System

## Overview

Build your roots, connect generations, and explore your family story through an interactive C++ family tree system. The Family Tree Management System is a powerful desktop application designed to help you organize, visualize, and manage your family relationships with ease.

## Features

- **Interactive Family Tree Visualization** - Visualize your family relationships in an intuitive and easy-to-understand format
- **Comprehensive Family Database** - Store and manage detailed information about family members
- **Relationship Management** - Track connections between family members across multiple generations
- **User-Friendly Interface** - Built with Qt for a smooth and responsive desktop experience
- **XML Export Functionality** - Export and save your complete family tree data in XML format for reliable data persistence
- **Cross-Platform Support** - Runs on Windows, macOS, and Linux systems

## Technology Stack

### Core Technologies

- **C++** (45.2%) - Core application logic and data structures
- **CMake** (7.5%) - Build system configuration
- **Makefile** (43.7%) - Build automation
- **QML** (3%) - User interface design
- **C** (0.5%) - Legacy/compatibility code
- **TypeScript** (0.1%) - Supporting scripts

### Key Libraries

- **Qt Framework** - Cross-platform GUI framework for building the desktop application
- **C++11 or higher** - Modern C++ standard for robust and efficient code

### ScreenShots
<img width="1919" height="967" alt="Screenshot 2026-10-01 223702" src="https://github.com/user-attachments/assets/471ea689-3103-404e-8943-96c0ce21e252" />
<img width="1917" height="968" alt="Screenshot 2026-10-01 223737" src="https://github.com/user-attachments/assets/560bb623-46ae-46c7-a068-183809ee8089" />
<img width="794" height="286" alt="Screenshot 2026-10-01 223925" src="https://github.com/user-attachments/assets/a2544ff5-0e20-44e4-9337-4873732e2ed0" />

## System Requirements

### Minimum Requirements

- **Operating System**: Windows 10+, macOS 10.14+, or Linux (Ubuntu 18.04+)
- **RAM**: 2 GB minimum
- **Disk Space**: 500 MB free space
- **Processor**: Dual-core processor

### Development Requirements

- **Qt Creator**: 5.0 or higher
- **Qt Framework**: 5.12 or higher
- **CMake**: 3.10 or higher
- **C++ Compiler**: GCC 7.0+, Clang 5.0+, or MSVC 2017+
- **Make**: GNU Make or compatible build tool

## Installation & Setup

### Prerequisites

Before you begin, ensure you have the following installed:

1. **Qt Creator** - Download from [Qt Official Website](https://www.qt.io/download)
2. **Qt Framework** - Typically included with Qt Creator
3. **CMake** - Install via package manager or [CMake Official Website](https://cmake.org/download/)
4. **C++ Compiler** - Install appropriate compiler for your OS

### Installation Steps

#### 1. Clone the Repository

```bash
git clone https://github.com/mTaqiii/Family-Tree-management-System.git
cd Family-Tree-management-System
```

#### 2. Install Dependencies

**On Windows:**
```bash
# If using vcpkg for package management
vcpkg install [required-packages]
```

**On macOS:**
```bash
# Using Homebrew
brew install cmake qt
```

**On Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential cmake qt5-qmake qt5-default
```

## Opening the Project in Qt Creator

### Step-by-Step Guide

#### Method 1: Using Qt Creator GUI (Recommended)

1. **Launch Qt Creator**
   - Open Qt Creator application on your system

2. **Open Project**
   - Click on `File` menu → `Open File or Project`
   - Navigate to your cloned repository folder
   - Select `CMakeLists.txt` or the project's `.pro` file

3. **Configure Project**
   - Qt Creator will detect the project type
   - Select your desired Qt kit (version and compiler)
   - Click `Configure Project` button
   - Choose your build configuration (Debug/Release)

4. **Build the Project**
   - Click `Build` menu → `Build Project "Family-Tree-management-System"`
   - Or use keyboard shortcut: `Ctrl+B` (Windows/Linux) or `Cmd+B` (macOS)

5. **Run the Application**
   - Click the green `Run` button (play icon) on the left side panel
   - Or use keyboard shortcut: `Ctrl+R` (Windows/Linux) or `Cmd+R` (macOS)

#### Method 2: Using Command Line

1. **Navigate to Project Directory**
   ```bash
   cd /path/to/Family-Tree-management-System
   ```

2. **Create Build Directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/5.x/gcc_64
   # For Windows: cmake .. -G "Visual Studio 16 2019"
   ```

4. **Build Project**
   ```bash
   make
   # On Windows: cmake --build .
   ```

5. **Run Application**
   ```bash
   ./Family-Tree-management-System
   # On Windows: Family-Tree-management-System.exe
   ```

## Project Structure

```
Family-Tree-management-System/
├── CMakeLists.txt          # CMake configuration file
├── Makefile                # Make build file
├── README.md               # This file
├── src/                    # Source files (C++)
├── include/                # Header files
├── ui/                     # QML UI components
├── resources/              # Application resources
└── build/                  # Build output directory (created after build)
```

## Usage Guide

### Getting Started

1. **Launch the Application** - Run the executable after building
2. **Create New Family Tree** - Start by creating a new family tree project
3. **Add Family Members** - Add individuals and their information
4. **Define Relationships** - Connect family members with relationships
5. **Explore Visualizations** - View the interactive family tree
6. **Export Family Tree** - Use the XML export option to save your complete family tree data

### Data Export and Persistence

The application provides an XML export feature that allows you to save your entire family tree data. This XML export serves as the primary data persistence mechanism, enabling you to:

- **Save Complete Family Data** - Export your family tree structure and member information
- **Backup Your Data** - Keep secure backups of your family information
- **Share Family Data** - Easily share XML files with family members
- **Data Portability** - Transfer your family tree data between systems

To export your family tree, use the export option available in the program's menu.

## Development

### Building from Source

#### Using CMake (Recommended)

```bash
cmake -B build -S .
cmake --build build --config Release
```

#### Using Make

```bash
make clean
make all
```

### Code Structure

- **Core Logic**: C++ classes for family tree data structures and algorithms
- **GUI Layer**: Qt/QML components for user interface
- **Data Layer**: XML-based persistence and file handling

## Contributing

We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is provided as-is. Please check the LICENSE file for more information.

## Support

For issues, questions, or suggestions:

- **Report Issues**: [GitHub Issues](https://github.com/mTaqiii/Family-Tree-management-System/issues)
- **Contact**: Reach out through GitHub

## Version History

- **v1.0** - Initial release

---

**Last Updated**: October 2026

**Repository**: [mTaqiii/Family-Tree-management-System](https://github.com/mTaqiii/Family-Tree-management-System)
