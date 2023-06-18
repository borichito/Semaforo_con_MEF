# Semaforo_con_MEF
Implementar mediante el modelo de Máquina de Estados Finitos (MEF) el antirrebote de teclas y la lógica de funcionamiento de un semáforo.
# Problema a resolver
Cuando se tienen los dos pulsantes leyendo entran en conflicto, por lo que para porbar el programa se debe usar un pulsante por un pulsante, esto se rezaliza comentando una linea en el archivo semaforo.h dentro del swith (colores), fsmButtonUpdate(*cleds.botones+1) (pulsante 2) , fsmButtonUpdate(*cleds.botones) (pulsante 1)
