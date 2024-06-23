import argparse
import subprocess
import os
import shutil

def run_command(command, work_dir):
    try:
        result = subprocess.run(command, cwd=work_dir, check=True, text=True, shell=True)
        print(f'Success: {result.args}')
    except subprocess.CalledProcessError as e:
        print(f'Error: {e}')
        print(f'Failed command: {e.cmd}')
        exit(1)

def build_project(build_dir='./build'):
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
    
    run_command('cmake ..', build_dir)
    run_command('make', build_dir)

def clean_project(build_dir='./build'):
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)
        print(f'Cleaned up {build_dir}')
    else:
        print(f'Build directory {build_dir} does not exist')

def format_code():
    source_dirs=['./include', './tests']
    cpp_files = []
    for source_dir in source_dirs:
        for subdir, dirs, files in os.walk(source_dir):
            for file in files:
                if file.endswith('.cpp') or file.endswith('.hpp'):
                    cpp_files.append(os.path.join(subdir, file))
    
    for file_path in cpp_files:
        run_command(f'clang-format -i {file_path}', None)
    print("Formatted all C++ files in the project.")
    
def run_tests(build_dir='./build'):
    run_command('ctest -V', build_dir)


def main():
    parser = argparse.ArgumentParser(description="Build and clean project using CMake.")
    parser.add_argument("--build", action="store_true", help="Build the project.")
    parser.add_argument("--clean", action="store_true", help="Clean the build directory.")
    parser.add_argument("--format", action="store_true", help="Format the source code.")
    parser.add_argument("--test", action="store_true", help="Run all tests.")
    parser.add_argument("--build-dir", default="build", help="Specify the build directory.")

    args = parser.parse_args()

    if args.clean:
        clean_project(args.build_dir)
    if args.format:
        format_code()
    if args.test:
        run_tests(args.build_dir)
    if args.build:
        build_project(args.build_dir)

if __name__ == "__main__":
    main()
