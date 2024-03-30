# Simple Third Person Shooter

Simple-Third-Person-Shooter is one of my early projects developed while learning Unreal Engine. It serves as a foundational project for creating a basic 3rd person shooter game, showcasing essential gameplay mechanics and AI behaviors.

## Key Features

### Character Movement and Aiming
- The character can move around the game world with their gun raised, aiming in the direction they are facing.
- A crosshair is provided to assist players in targeting enemies accurately.
- The character has the ability to jump, adding verticality to the gameplay.

### Enemy AI and Behavior
- Enemy placements are static, and they become active when the player enters their line of sight.
- When an enemy detects the player, it will chase them relentlessly.
- If the enemy catches up to the player within a certain distance, it will begin shooting at them.
- If the player manages to escape and break the enemy's line of sight, the enemy will continue to chase them to their last known location.
- After a certain amount of time, if the enemy loses sight of the player, it will return to its designated patrol position.

### Boss Enemy
- The game features a boss enemy, which exhibits similar behavior to the regular enemies but possesses increased health, making it more challenging to defeat.

### Assets and Resources
- All assets used in this project are sourced from Unreal Engine's own library, ensuring high-quality visuals and seamless integration with the engine.

## Acknowledgments
This project was developed by following the course "Unreal Engine C++ Developer: Learn C++ and Make Video Games" on Udemy (https://www.udemy.com/course/unrealcourse/). The course provided valuable guidance and instruction throughout the development process.
