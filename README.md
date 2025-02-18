# Air Hockey  

Air Hockey is a computer game developed in C++ using the SFML library. The game is written in Polish language. 

![image](https://github.com/user-attachments/assets/7a302ffe-89f5-4890-a18d-32905db05415)  
![image](https://github.com/user-attachments/assets/f190b588-99cf-421a-b3a2-3844f9f242bc)  
![image](https://github.com/user-attachments/assets/1c96d375-7d10-40ec-a3f8-1904b063e717)  
![image](https://github.com/user-attachments/assets/ba290b0f-6678-432a-a4b4-07251d0c94b1)  

## Description  

The game simulates an Air Hockey match where two players compete by moving within their half of the board, trying to hit the puck into the opponent's goal.  
It features a main menu, options (such as changing the background and adjusting the number of goals), and a help section.  
Air Hockey allows two players to compete against each other in various matchups.  
The game utilizes the SFML library for 2D graphics rendering and user interaction.  

## Features  

- **Two-player mode**: Compete against a friend on the same computer.  
- **Simple interface**: Intuitive controls and a clear user interface.  
- **Dynamic gameplay**: Fast-paced and exciting action.  

## Requirements  

- **Operating System**: Windows, Linux, or macOS  
- **SFML Library**: You must install the SFML library compatible with your operating system.  

## Installation  

1. **Clone the repository**:  

   ```bash
   git clone https://github.com/jrozycki2003/Cymbergaj.git
   ```  

2. **Install the SFML library**:  

   - **Windows**: Download and install SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php).  
   - **Linux**: Use a package manager, e.g., `sudo apt-get install libsfml-dev` for Debian-based systems.  
   - **macOS**: Install SFML via Homebrew: `brew install sfml`.  

3. **Compile the project**:  

   - Navigate to the project directory:  

     ```bash
     cd Cymbergaj
     ```  

   - Use a C compiler, such as GCC, to compile the project:  

     ```bash
     g++ -o air_hockey main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```  

## Usage  

After compiling the project, run the game using the command:  

```bash
./air_hockey
```  

Controls:  
- **Player 1**: Arrow keys  
- **Player 2**: W, A, S, D  

## Contact  

For questions or suggestions, feel free to reach out.  
