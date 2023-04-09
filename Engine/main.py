import mygameengine as engine


def main():
    # Create an instance of the Engine class
    game_engine = engine.Engine()

    # Initialize the subsystems
    if not game_engine.InitializeGraphicsSubSystem():
        print("Failed to initialize the graphics subsystem.")
        return

    game_engine.InitializeResourceSubSystem()
    game_engine.InitializeSceneManagerSubSystem()

    scene_manager = engine.SceneManager.get_instance()
    scene_manager.add_test_game_objects()

    game_engine.Start()
    game_engine.MainGameLoop()

    game_engine.Shutdown()


if __name__ == "__main__":
    main()
