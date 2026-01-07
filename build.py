import os
import subprocess
import sys

def build_project():
    # Recherche de tous les fichiers .cpp dans le dossier actuel et sous-dossiers
    sources = []
    for root, dirs, files in os.walk("."):
        for file in files:
            if file.endswith(".cpp"):
                sources.append(os.path.join(root, file))

    # Dossiers d'inclusion (Header files .h)
    include_dirs = [
        "-I.",                       # Le dossier courant
        "-Ithirdparty/SDL3/include", # SDL3 headers 
        "-Ithirdparty/imgui"         # ImGui headers 
    ]

    # Bibliothèques à lier selon le système d'exploitation
    libraries = []
    if sys.platform == "win32":
        # Windows
        libraries = ["-lSDL3", "-limm32"] 
    elif sys.platform == "darwin":
        # MacOS
        libraries = ["-lSDL3", "-framework Cocoa"]
    else:
        # Linux / Autres
        libraries = ["-lSDL3", "-ldl", "-lpthread"]

    # Commande de compilation avec clang++
    cmd = [
        "g++",
        "-std=c++17",    # Standard C++17 requis 
        "-Wall",         # Affiche tous les avertissements
        "-g",            # Ajoute les infos de debug 
        *include_dirs,
        *sources,
        *libraries,
        "-o", "mygame"   # Nom de l'exécutable final 
    ]

    # Exécution de la commande
    print("Compilation en cours...")
    try:
        subprocess.run(cmd, check=True)
        print("Succès ! Exécutable 'mygame' créé.")
    except subprocess.CalledProcessError:
        print("Erreur lors de la compilation.")
    except FileNotFoundError:
        print("Erreur : Le compilateur 'clang++' n'a pas été trouvé. Assurez-vous qu'il est installé.")

if __name__ == "__main__":
    build_project()