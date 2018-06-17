Hi! I’m really excited that you are interested in contributing to Gribot. Before submitting your contribution though, please make sure to take a moment and read through the following guidelines:
- [Code of Conduct](https://github.com/guycorbaz/gribot/blob/master/CODE_OF_CONDUCT.md)
- [Issue Reporting Guidelines](#issue-reporting-guidelines)
- [Pull Request Guidelines](#pull-request-guidelines)
- [Project Structure](#project-structure)

## Issue Reporting Guidelines


## Pull Request Guidelines
- The `master` branch is basically just a snapshot of the latest stable release. All development should be done in dedicated branches. **Do not submit PRs against the `master` branch.**
- Checkout a topic branch from the relevant branch, e.g. `dev`, and merge back against that branch.
- It's OK to have multiple small commits as you work on the PR - we will let GitHub automatically squash it before merging.
- If adding new feature:
  - Add accompanying test case.
  - Provide convincing reason to add this feature. Ideally you should open a suggestion issue first and have it greenlighted before working on it.
- If fixing a bug:
  - If you are resolving a special issue, add `(fix #xxxx[,#xxx])` (#xxxx is the issue id) in your PR title for a better release log, e.g. `update entities encoding/decoding (fix #3899)`.
  - Provide detailed description of the bug in the PR. Live demo preferred.
  - Add appropriate test coverage if applicable.
  
  ## Project structure
  
    - **`config`**: contains configuration files for the different nodes used by Gribot
    - **`launch`**: contains gribot lauch files
    - **`scripts`**: contains scripts used by the different modules. Example: the CANbus starting script
    - **`urdf`**: contains the robot description files in urdf and/or xacro format.
    - **`src`**: contains Gribot nodes source code files
    
  ## Financial contribution
  
  As a pure community-driven project without major corporate backing, we also welcome financial contributions via
   [Gribot donation page](https://gribot.org/donations/donation/).
   
   All funds will be used exclusively for the development of the [Gribot](https://www.gribot.org) project.
