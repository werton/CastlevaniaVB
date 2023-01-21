import os
import subprocess
import time

project_dir = os.path.abspath("..\\..\\..\\..\\projects\\Micetopia\\")
scripts_dir = os.path.abspath("..\\..\\..\\..\\devkit\\dev_tools\\scripts\\")


def get_path(path):
    return os.path.join(os.path.abspath(project_dir), path)

def tiled_save_tmx_as_new(input_name, output_name):
    path = os.path.abspath("..\\..\\..\\..\\devkit\\dev_tools\\Tiled\\tiled.exe")
    subprocess.run([path, "--export-map", "tmx", input_name, output_name])


def aseprite_do_indexed(input_name, output_name):
    aseprite = os.path.abspath("..\\..\\..\\..\\devkit\\dev_tools\\Aseprite1.3beta21\Aseprite.exe")
    subprocess.run(
        [aseprite, "-b", input_name, "--dithering-algorithm", "ordered", "--color-mode", "indexed", "--save-as", output_name])


def get_file_list(folder, extension, add_folder_path=False):
    if add_folder_path:
        return [os.path.join(folder, file) for file in os.listdir(folder) if file.lower().endswith(extension)]
    else:
        return [file for file in os.listdir(folder) if file.lower().endswith(extension)]


def write_collisions(file_list, target_file_c, target_file_h):
    args = " ".join(file_list)
    command = os.path.join(scripts_dir, "collisionGenerator.py") + " " + target_file_c + " " + target_file_h + " " + args
    print(command)
    os.system(command)


def tmx_extract_class_name(file):
    command = os.path.join(scripts_dir, "tmxClassTrimmer.py" + " " + file + " " + file)
    print(command)
    os.system(command)


def generate_tilemap_res(folders_path_list, file_for_write):
    args = " ".join(folders_path_list)
    command = os.path.join(scripts_dir, "resMapGenerator.py" + " " + file_for_write + " " + args)
    print(command)
    os.system(command)


def all_in_folder_tmx_extract_class_name(folder):
    for file in os.listdir(folder):
        if file.lower().endswith(".tmx"):
            tmx_extract_class_name(os.path.join(folder, file))


def all_in_folder_tmx_convert_to_new(folder):
    for file in os.listdir(folder):
        if file.lower().endswith(".tmx"):
            file_name = os.path.join(folder, file)
            print(file_name + " converting to 1.92 tmx...")
            tiled_save_tmx_as_new(file_name, file_name)
            print("Done.")


if __name__ == '__main__':

    print("# ======= Copy layer images and convert them as 8bpp png =======")
    source_dir = get_path("development\\maps\\cave\\simplified\\")
    target_dir = get_path("res\\levels\\")
    level_folder_names = next(os.walk(source_dir))[1]

    for level in level_folder_names:
        level_folder_full_path = os.path.join(source_dir, level)
        source_level_dir = os.path.join(source_dir, level)
        target_level_dir = os.path.join(target_dir, level)
        print("Aseprite " + level + " converting to 8bpp...")
        aseprite_do_indexed(os.path.join(source_level_dir, "layer_a.png"), os.path.join(target_level_dir, "layer_a.png"))
        aseprite_do_indexed(os.path.join(source_level_dir, "layer_b.png"), os.path.join(target_level_dir, "layer_b.png"))
        print("Done.")

    print("# ======= Copy map files to Levels dir and save them as 1.92 TMX version =======")
    work_dir = get_path("development\\maps\\cave\\tiled\\")
    target_dir = get_path("res\\levels\\")
    level_folder_names = next(os.walk(target_dir))[1]

    for file in os.listdir(work_dir):
        if file.lower().endswith(".tmx"):
            target_file = os.path.join(target_dir, file)
            tiled_save_tmx_as_new(os.path.join(work_dir, file), os.path.join(target_dir, file[5:-4], "objects.tmx"))
            print(os.path.join(target_dir, file[5:-4], "objects.tmx"))

    time.sleep(0.1)

    print("# ======= trim class name from object name =======")
    work_dir = os.getcwd()

    source_dir = get_path("res\\levels\\")
    level_folder_names = next(os.walk(source_dir))[1]

    for level in level_folder_names:
        level_folder_full_path = os.path.join(source_dir, level)
        print(level_folder_full_path)
        all_in_folder_tmx_extract_class_name(level_folder_full_path)

    print("# ======= writing collisions =======")
    source_dir = get_path("development\\maps\\cave\\simplified\\")
    target_file_c = get_path("src\\colmap.c")
    target_file_h = get_path("inc\\colmap.h")
    level_folder_names = next(os.walk(source_dir))[1]

    file_list = []

    for level in level_folder_names:
        file_list.extend(get_file_list(os.path.join(source_dir, level), ".csv", add_folder_path=True))

    write_collisions(file_list, target_file_c, target_file_h)

    print("# ======= create tilemap.res =======")
    source_dir = get_path("res\\levels\\")
    target_file = get_path("res\\tilemaps.res")
    level_folder_names = next(os.walk(source_dir))[1]
    folders_path_list = [os.path.join(source_dir, folder) for folder in level_folder_names]

    generate_tilemap_res(folders_path_list, target_file)

    print("Finished.")
