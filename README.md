# Pipex-42

## Description

Pipex-42 is a project that aims to recreate the functionality of the shell command pipeline (`|`) in C. It involves creating a program that takes two file paths and two commands as arguments, and then executes the commands in a pipeline, redirecting the input and output to the specified files.

## Getting Started

To get started with Pipex-42, follow these steps:

1. Clone the repository
2. Navigate to the project directory: `cd pipex-42`
3. Compile the program: `make`
4. Run the program with the required arguments: `./pipex file1 cmd1 cmd2 file2`

## Usage

The Pipex-42 program takes four arguments:

1. `file1`: The input file.
2. `cmd1`: The first command to be executed.
3. `cmd2`: The second command to be executed.
4. `file2`: The output file.

Example usage: `./pipex infile "ls -l" "grep foo" outfile`

## Contributing

Contributions to Pipex-42 are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

Pipex-42 is licensed under the [MIT License](https://opensource.org/licenses/MIT).
