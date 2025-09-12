# Project Overview

This project is a fork of the Newlib C Library, with modifications to support
the Nanvix operating system.

## Target Architecture Support

This fork introduces the following new target architectures and operating system support:
- `i686-nanvix` (32-bit x86 for Nanvix)

## Building and Installation

This project uses a custom `z` utility script for streamlined building and installation.

### Quick Start

```bash
# See all available commands
./z help

# Complete build process
./z setup      # Install required system packages
./z configure  # Configure the build
./z build      # Compile the source code
./z install    # Install to default location
./z release    # Create a release zip file
```

## Contributing Guidelines

### Branch Naming Convention

Use these prefixes for branches:
- `enhancement-*` - Feature enhancements
- `feature-*` - New features
- `bugfix-*` - Bug fixes
- `dependabot/*` - Dependency updates created by Dependabot
- `copilot/*` - AI-assisted development
