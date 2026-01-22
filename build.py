import os
import subprocess
import sys

def build_project():
    print("--- 🔨 DÉBUT DE LA COMPILATION (Mode Recherche Totale) ---")

    # 1. Recherche de TOUS les fichiers .cpp (Racine + src)
    sources = []
    # On regarde dans le dossier courant (.) et dans src
    directories_to_check = [".", "src", "libs/imgui"]
    
    for directory in directories_to_check:
        if os.path.exists(directory):
            for file in os.listdir(directory):
                if file.endswith(".cpp"):
                    path = os.path.join(directory, file)
                    sources.append(path)
                    print(f"   [+] Fichier trouvé : {path}")

    # Vérification
    if len(sources) == 0:
        print("❌ ERREUR CRITIQUE : Aucun fichier .cpp trouvé !")
        return

    # 2. Configuration des dossiers Include (.h)
    include_dirs = [
        "-I.",                       
        "-Iinclude",                 
        "-Isrc",                     
        "-Ithirdparty/SDL3/include" ,
        "-Ilibs/imgui"
    ]

    # 3. Bibliothèques
    libraries = ["-Llib","-lSDL3","-lSDL3_image"]

    # 4. Commande de compilation
    cmd = [
        "g++", "-std=c++17", "-g",
        *include_dirs,   
        *sources,        
        *libraries,      
        "-o", "Flappy_Bird_by_Game_Changer "   
    ]

    # 5. Exécution
    try:
        subprocess.run(cmd, check=True)
        print("\n✅ SUCCÈS ! Votre jeu est prêt.")
        print("👉 Tapez 'Flappy_Bird_by_Game_Changer' pour jouer.")
    except subprocess.CalledProcessError:
        print("\n❌ ÉCHEC DE LA COMPILATION.")

if __name__ == "__main__":
    build_project()