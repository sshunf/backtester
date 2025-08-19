# Backtester

## Getting Started

This guide will help you set up the project locally. We use **Poetry** for dependency management and **pre-commit** hooks to ensure consistent code quality.

## Prerequisites

Before you begin, make sure you have the following tools installed on your system:

* [**Poetry**](https://python-poetry.org/docs/#installation): A tool for dependency management and packaging in Python.
* [**pre-commit**](https://pre-commit.com/#install): A framework for managing and maintaining multi-language pre-commit hooks.

## Setup Instructions

Follow these steps to get your local development environment ready.

### 1. Clone the Repository

Clone the project from GitHub and navigate into the directory.

```bash
git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
cd your-repo-name
```

### 2. Install Dependencies

Use Poetry to install all the project's dependencies and development tools. This command will create a virtual environment and install all packages listed in the `pyproject.toml` and `poetry.lock` files.

```bash
poetry install
```

### 3. Install Pre-Commit Hooks

This step is crucial and only needs to be done once. It activates the pre-commit hooks that will automatically run checks before every commit, such as code formatting and static type checking.

```bash
pre-commit install
```

## Running Common Commands

To run project-specific commands, you can use `poetry run` which executes the command within the project's virtual environment.

* **Run tests with pytest:**
    ```bash
    poetry run pytest
    ```

* **Run type checks with mypy:**
    ```bash
    poetry run mypy .
    ```

* **Run code format checks and linting with ruff:**
    ```bash
    poetry run ruff .
    poetry run ruff format .
