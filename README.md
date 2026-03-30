Un pequeño engine para poder manejar de mejor manera los nuevos contenidos de LearnOpenGL, es bastante basico y no deberia usarse de ejemplo.

Para compilar usar CMAKE con comando:

´´´
cmake -B build --fresh -S .
´´´

Recomendado usar ninja

´´´
cmake -B build --fresh -S . -G Ninja 
´´´
