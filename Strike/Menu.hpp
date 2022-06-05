#include "imgui/imgui.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi.h>
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "Globals.hpp"
#include "util.h"
#include "Pawn.hpp"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;


namespace Menu
{
    static char WeaponId[128] = "WID_Shotgun_SemiAuto_Athena_R_Ore_T03";
	void MenuTheme()
	{
        ImGui::GetStyle().FrameRounding = 4.0f;
        ImGui::GetStyle().GrabRounding = 4.0f;

        ImVec4* colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

    Present oPresent;
    HWND window = NULL;
    WNDPROC oWndProc;
    ID3D11Device* pDevice = NULL;
    ID3D11DeviceContext* pContext = NULL;
    ID3D11RenderTargetView* mainRenderTargetView;
    bool Menu = true;

    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    bool init = false;
    HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

    void InitImGui()
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(pDevice, pContext);
    }

    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
    }

    HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
    {
        if (!init)
        {
            if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
            {
                pDevice->GetImmediateContext(&pContext);
                DXGI_SWAP_CHAIN_DESC sd;
                pSwapChain->GetDesc(&sd);
                window = sd.OutputWindow;
                ID3D11Texture2D* pBackBuffer;
                pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
                pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
                pBackBuffer->Release();
                oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
                InitImGui();
                init = true;
            }

            else
                return oPresent(pSwapChain, SyncInterval, Flags);
        }

        if (GetAsyncKeyState(VK_F4) && 0x01)
            Menu = !Menu;

        if (Globals::Fort == FortState::EFortInGame && Menu)
        {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Project Strike");
            ImGui::SetWindowSize(ImVec2(500, 300));
            ImGui::BeginTabBar("TabBar");
            if (ImGui::BeginTabItem("Main"))
            {
                ImGui::Text("Main");
                ImGui::Separator();
                //    ImGui::SliderFloat("FOV", &FOV, 0.0f, 100.0f);
                //    //if slider is changed
               //     if (FOV != 0)
               //     {
                //
               //     }

                ImGui::Button("Become Thanos");
                if (ImGui::IsItemClicked())
                {
                    MessageBoxA(NULL, "Thanos Hasn't Been Added Yet.", "Strike", NULL);
                }

                ImGui::Button("Kill Player");
                if (ImGui::IsItemClicked())
                {
                    Globals::Pawn->ForceKill(SDK::FGameplayTag(), &SDK::AController(), &SDK::AActor());
                }

                ImGui::Button("Respawn");
                if (ImGui::IsItemClicked())
                {
                    World::SpawnActor(SDK::APlayerPawn_Athena_C::StaticClass(), SDK::FVector{ 0, 0, 5000 }, {});
                    Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortPlayerPawnAthena::StaticClass(), &Globals::Actors);

                    auto Pawn = reinterpret_cast<SDK::AFortPlayerPawnAthena*>(Globals::Actors[0]);

                    Globals::Pawn = Pawn;
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Weapons"))
            {
                ImGui::Text("Weapons");
                ImGui::Separator();
                ImGui::Text("Enter weapon ID");
                ImGui::InputText("Weapon ID", WeaponId, 128);
                ImGui::Button("Give Weapon");
                if (ImGui::IsItemClicked())
                {
                    if (std::string(WeaponId).contains("Harvest") || std::string(WeaponId).contains("Pickaxe"))
                    {
                        Pawn::EquipWeapon("FortWeaponMeleeItemDefinition", std::string(WeaponId));
                    }
                    else
                    {
                            Pawn::EquipWeapon("FortWeaponRangedItemDefinition", std::string(WeaponId));
                    }
                }
                //     ImGui::Button("Remove");
                //     if (ImGui::IsItemClicked())
               //      {
                 //    }

                //     ImGui::Button("Add Max Ammo");

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Map"))
            {
                ImGui::Text("Map");
                ImGui::Separator();
                //   ImGui::Button("Teleport to top of map");
               //    if (ImGui::IsItemClicked())
               //    {
               //    }

                ImGui::Button("Destroy All Actors");
                if (ImGui::IsItemClicked())
                {
                    const int result = MessageBox(NULL, L"Are You Sure You Want To Continue?", L"Strike", MB_YESNOCANCEL);

                    switch (result)
                    {
                    case IDYES:
                        Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AActor::StaticClass(), &Globals::Actors);
                        for (int i = 0; i < Globals::Actors.Num(); i++)
                        {
                            reinterpret_cast<SDK::AActor*>(Globals::Actors[i])->K2_DestroyActor();
                        }
                        break;
                    case IDNO:
                        break;
                    case IDCANCEL:
                        break;
                    }
                }
                ImGui::Separator();
                //    ImGui::SliderFloat("Time", &time, 12.0f, 24.0f);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Credits"))
            {
                ImGui::Text("Credits");
                ImGui::Separator();
                ImGui::Text("- DRQSuperior");
                ImGui::Text("- nax#1800");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
            ImGui::End();
            ImGui::Render();

            pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
        return oPresent(pSwapChain, SyncInterval, Flags);
    }
}