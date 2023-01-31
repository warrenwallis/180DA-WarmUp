import random as rand

def main():
    print('Playing Rock-Paper-Scissors')

    while True:
        user_gesture = int(input('Input 0 for Rock, 1 for Paper, 2 for Scissors: '))
        comp_gesture = rand.randint(0,2)
        mapping = {0 : 'Rock', 1 : 'Paper', 2 : 'Scissors'}
        
        if user_gesture == (comp_gesture-1)%3:
            print(f'Computer chooses {mapping[comp_gesture]}; Computer wins!')
        elif comp_gesture == (user_gesture-1)%3:
            print(f'Computer chooses {mapping[comp_gesture]}; You win!')
        else:
            print(f'Computer chooses {mapping[comp_gesture]}; Tie!')
        
        

if __name__ == '__main__':
    main()