#include "sglpch.h"

#include "SGL/tests/TestMenu.h"
#include "SGL/tests/TestClearColor.h"
#include "SGL/tests/TestTexture2D.h"
#include "SGL/tests/TestBatchRendering.h"

#include "SGL/Renderer.h"

static constexpr float ASPECT_RATIO = 16.f / 9.f;
static constexpr int WINDOW_HEIGHT = 1080;
static constexpr int WINDOW_WIDTH = static_cast<int>(WINDOW_HEIGHT * ASPECT_RATIO);

static constexpr float IMGUI_FONT_SCALE = 2.f;

static constexpr glm::vec4 DEFAULT_CLEAR_COLOR = { 0.f, 0.f, 0.f, 1.f }; // Black

static constexpr const char* TEST_MENU_NAME = "Test Menu";

static void RegisterMenus(test::TestMenu& testMenu)
{
    testMenu.RegisterTest<test::TestClearColor>("Clear Color");
    testMenu.RegisterTest<test::TestTexture2D>("Texture 2D", WINDOW_WIDTH, WINDOW_HEIGHT);
    testMenu.RegisterTest<test::TestBatchRendering>("Batch Rendering", WINDOW_WIDTH, WINDOW_HEIGHT);
}

static void glfwErrorCallback(const int error, const char* const description)
{
    fprintf(stderr, "[GLFW Error] %d: %s\n", error, description);
}

int main()
{
    glfwSetErrorCallback(glfwErrorCallback);

    AssertReturnIf(glfwInit() != GLFW_TRUE, EXIT_FAILURE);

    static constexpr const char* GLSL_VERSON = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef SGL_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    auto* const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        SGL_ASSERT(false);
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        SGL_ASSERT(false);
        return EXIT_FAILURE;
    }

#ifdef SGL_DEBUG
    sgl::EnableGlDebugOutput();
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSON);

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    SGL_LOG_INFO("OpenGL Version: %s", glGetString(GL_VERSION));

    {
        const sgl::Renderer renderer{};
        renderer.EnableBlending();

        test::TestMenu testMenu(TEST_MENU_NAME);
        RegisterMenus(testMenu);

        float dt = 0.f;
        while (!glfwWindowShouldClose(window))
        {
            const auto t1 = chrono::high_resolution_clock::now();

            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            renderer.SetClearColor(DEFAULT_CLEAR_COLOR);
            renderer.Clear();

            if (auto* currentTest = testMenu.GetCurrentTest())
            {
                currentTest->OnUpdate(dt);
                currentTest->OnRender(renderer);

                ImGui::Begin(currentTest->GetName());
                ImGui::SetWindowFontScale(IMGUI_FONT_SCALE);

                if (!testMenu.IsCurrentTestSelf())
                {
                    if (ImGui::Button("<-"))
                    {
                        testMenu.SetCurrentTestToSelf();
                        currentTest = testMenu.GetCurrentTest();
                    }
                    ImGui::NewLine();
                }

                currentTest->OnImGuiRender();

                if (!testMenu.IsCurrentTestSelf())
                {
                    ImGui::NewLine();
                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                }

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            const auto t2 = chrono::high_resolution_clock::now();
            dt = chrono::duration<float>(t2 - t1).count();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}