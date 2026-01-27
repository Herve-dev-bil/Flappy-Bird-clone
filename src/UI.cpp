#include "UI.h"
#include <string>

#include "UI.h"

void UI::Init(SDL_Window* window, SDL_Renderer* renderer)
{
    // 1. Initialisation du contexte
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // 2. Style
    ImGui::StyleColorsDark();

    // 3. Connexion avec SDL3
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void UI::Shutdown()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void UI::ProcessEvent(SDL_Event* event)
{
    // On passe l'événement à ImGui (clic souris, touche clavier...)
    ImGui_ImplSDL3_ProcessEvent(event);
}

void UI::Draw(SDL_Renderer* renderer, GameState state, int score, int highScore, bool& startGame, bool& restart, bool& quit)
{
    // Début de la frame ImGui
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Récupérer la taille de la fenêtre SDL pour centrer les menus
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 centerPos = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);

    //1. ÉCRAN D'ACCUEIL
    if (state == STATE_MENU)
    {
        // On centre la fenêtre
        ImGui::SetNextWindowPos(centerPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(300, 200));
         
        // On crée une fenêtre sans barre de titre ("NoDecoration") et qui ne bouge pas ("NoMove")
        ImGui::Begin("Bienvenue", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        
        // Texte centré
        float windowWidth = ImGui::GetWindowSize().x;
        float textWidth = ImGui::CalcTextSize("FLAPPY BIRD CLONE").x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "FLAPPY BIRD CLONE");
        
        ImGui::Separator();
        ImGui::Spacing();
        
        // Affichage du Record
        std::string recordText = "Meilleur Score : " + std::to_string(highScore);
        textWidth = ImGui::CalcTextSize(recordText.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text("%s", recordText.c_str());

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Bouton JOUER (Gros bouton)
        if (ImGui::Button("JOUER (Espace)", ImVec2(-1, 40))) // -1 signifie "toute la largeur"
        {
            startGame = true;
        }

        ImGui::Spacing();

        if (ImGui::Button("Quitter", ImVec2(-1, 40)))
        {
            quit = true;
        }

        ImGui::End();
    }

    //2.EN JEU
    else if (state == STATE_PLAYING)
    {
        // On affiche juste le score en haut au milieu, sans fond de fenêtre
        ImGui::SetNextWindowPos(ImVec2(centerPos.x, 20), ImGuiCond_Always, ImVec2(0.5f, 0.0f));

        // Fond transparent (Alpha = 0.3f) pour voir le ciel derrière
        ImGui::SetNextWindowBgAlpha(0.3f); // Fond transparent
        
        ImGui::Begin("ScoreOverlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Score : %d", score);
        ImGui::End();
    }

    //3.GAME OVER
    else if (state == STATE_GAME_OVER)
    {
        ImGui::SetNextWindowPos(centerPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(300, 250));

        ImGui::Begin("GameOver", nullptr, ImGuiWindowFlags_NoDecoration);

        // Texte GAME OVER en Rouge
        float windowWidth = ImGui::GetWindowSize().x;
        float textWidth = ImGui::CalcTextSize("GAME OVER").x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

        // Texte en ROUGE pour signaler la mort
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "GAME OVER");

        ImGui::Separator();
        ImGui::Spacing();

        // Scores
        ImGui::Text("Score de la partie : %d", score);
        ImGui::Text("Meilleur Score     : %d", highScore);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Boutons
        if (ImGui::Button("Recommencer (Espace)", ImVec2(-1, 40)))
        {
            restart = true;
        }

        ImGui::Spacing();

        if (ImGui::Button("Quitter", ImVec2(-1, 40)))
        {
            quit = true;
        }

        ImGui::End();
    }

    // Rendu final
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}