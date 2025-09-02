import sys
import kociemba

def main():
    try:
        # The cube string is passed as the first argument
        if len(sys.argv) < 2:
            return

        cubestring = sys.argv[1].strip()

        if len(cubestring) != 54:
            return

        # Solve the cube and print the solution
        solution = kociemba.solve(cubestring)
        print(solution, end='')

    except Exception:
        return

if __name__ == "__main__":
    main()