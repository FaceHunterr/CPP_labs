
#include <iostream>
#include "functions.h"


int main(int argc, char** argv) {

  if (argc < 2) {
    std::cerr << "Not enough command line arguments!\n";
    return 1;
  }
  std::ifstream inputFile;
  inputFile.open(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "Unable to open file!\n";
    return 1;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  MenuCreating(inputFile);

  glutDisplayFunc(Display);
  glutIdleFunc(Display);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(motion);

  glutMainLoop();
  EndWork();
  return EXIT_SUCCESS;
}