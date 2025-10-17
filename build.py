import subprocess

file_list = ["main", "src/glad"]
compile_list = ["main", "glad"]

include_list = ["include/"]

link_list = ["SDL3", "opengl32"]


def create_args():
    args = {
        "compile": ["g++", "-c"],
        "build": ["g++"]
    }


    for file in file_list:
        args["compile"].append(file + ".cpp")

    for file in compile_list:
        args["build"].append(file + ".o")
    
    for include_path in include_list:
        args["compile"].append(f"-I{include_path}")
    
    for lib in link_list:
        args["build"].append(f"-l{lib}")
    
    args["build"].append("-o")
    args["build"].append("engine")
    
    return args

args = create_args()
for arg in args:
    process = subprocess.run(args[arg])

    print("Error: ", process.stderr)
    print("Output: ", process.stdout)

    


    