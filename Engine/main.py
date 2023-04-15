import mygameengine as engine

TEMP_WIDTH = 50
TEMP_HEIGHT = 50


def main():
    """
    Initializes the engine and creates a game object with components.

    Returns:
        None
    """

    # Create an instance of the Engine class
    game_engine = engine.Engine()

    # Initialize the graphics, resource, and scene manager subsystems
    if not game_engine.initialize_graphics_subsystem():
        print("Failed to initialize the graphics subsystem.")
        return

    game_engine.initialize_resource_subsystem()
    game_engine.initialize_scene_manager_subsystem()

    # Get the instance of the scene manager
    scene_manager = engine.SceneManager.get_instance()

    # Create components for the main character
    scene_manager.create_component('main-character-controller-component',
                                   'CONTROLLER')
    scene_manager.create_component('main-character-transform-component',
                                   'TRANSFORM')
    scene_manager.create_component('main-character-collision-component',
                                   'COLLISION')
    scene_manager.create_component('main-character-sprite-component', 'SPRITE')

    # Create a game object for the main character
    scene_manager.create_game_object('main-character-game-object', 'DEFAULT',
                                     100, 100, TEMP_WIDTH, TEMP_HEIGHT)

    # Attach the components to the game object
    scene_manager.add_component('main-character-game-object',
                                'main-character-controller-component')
    scene_manager.add_component('main-character-game-object',
                                'main-character-transform-component')
    scene_manager.add_component('main-character-game-object',
                                'main-character-collision-component')
    scene_manager.add_component('main-character-game-object',
                                'main-character-sprite-component')

    # Enable collision for the main character
    scene_manager.add_collision_object('main-character-game-object')

    # Add the game object to the scene
    scene_manager.add_game_object('main-character-game-object')

    # Start the engine and run the main game loop
    game_engine.start()
    game_engine.main_game_loop()

    # Shutdown the engine
    game_engine.shutdown()


if __name__ == "__main__":
    main()