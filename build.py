import os
import subprocess
import sys

def build_project():
    print("--- 🔨 DÉBUT DE LA COMPILATION (Mode Architecture Pro) ---")

    # 1. On cherche tous les fichiers .cpp dans le dossier 'src'
    sources = []
    # On regarde aussi à la racine au cas où, et dans src
    search_dirs = [".", "src"]
    
    for folder in search_dirs:
        if os.path.exists(folder):
            for file in os.listdir(folder):
                if file.endswith(".cpp"):
                    # On crée le chemin complet (ex: src/Game.cpp)
                    path = os.path.join(folder, file)
                    sources.append(path)
                    print(f"   [+] Fichier trouvé : {path}")

    if not sources:
        print("❌ ERREUR : Aucun fichier .cpp trouvé ! Vérifiez vos dossiers.")
        return

    # 2. On dit au compilateur où sont les fichiers .h (include)
    include_dirs = [
        "-I.",                       
        "-Iinclude",                 # Regarde dans le dossier include
        "-Ithirdparty/SDL3/include", 
        "-Ithirdparty/imgui"         
    ]

    # 3. Les bibliothèques (Windows)
    libraries = ["-lSDL3", "-limm32"]

    # 4. La commande finale
    cmd = [
        "g++",           
        "-std=c++17",    
        "-Wall",         
        "-g",            
        *include_dirs,   
        *sources,        
        *libraries,      
        "-o", "mygame"   
    ]

    # 5. On lance !
    try:
        subprocess.run(cmd, check=True)
        print("\n✅ SUCCÈS ! Votre jeu est prêt.")
        print("👉 Tapez 'mygame.exe' pour jouer.")
    except subprocess.CalledProcessError:
        print("\n❌ ÉCHEC. Regardez les erreurs rouges ci-dessus.")

if __name__ == "__main__":
    build_project()