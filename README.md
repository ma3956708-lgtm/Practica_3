# Práctica [3]: [Horno]

## Descripción
[Se trata de un tipo horno casero donde con ayuda de un foco incandesente
calentamos el interior del horno y con ayuda de dos ventiladores y celda 
peltier enfriamos el interior, tomando temperatura con un sensor DS18B20
mostrando la temperatura a la que se encuentra.]

## Objetivo
[Aprender el funcionamiento de un convertidor de escala para adoptarlo en
cualquier aplicacion y aprender a usar el microcontrolador ESP32.]

## Integrantes
- [Miguel Angel Ramirez Elias]
- [Francisco Emmanuel Hernandez Camacho]
- [Diego Gomez Muñis]
- [Yessenia Medrano Castillo]
- [Fernanda Jaqueline Ibarra Romero]

## Componentes
- ESP32
- [Sensor, pantalla LCD I2C, relays, botones, foco incandesente, soquet, etc.]

## Conexiones
| Componente | Pin del ESP32 |
|------------|---------------|
| [Sensor]   | GPIO [4]      |
| [LCD SDA]  | GPIO [21]     |
| [LCD SCL]  | GPIO [22]     |
| [Foco]     | GPIO [17]     |
| [Fans]     | GPIO [16]     |
| [Peltier]  | GPIO [16]     |

## Funcionamiento
[Cómo trabaja el programa: qué lee, qué decide y qué activa. Si hay botones o límites ajustables, explica para qué sirve cada uno.
Limitamos los noveles a lo que el sensor puede detectar con un nivel bajo y un nivel alto, cuando uno de estos dos se excede sucede
que activa ya sea el foco cuando el sensor marque por debajo del nivel bajo para calentar y de lo contrario si se excede el nivel alto se apaga el foco y se enciende los ventiladores con celda peltier; de igual forma se puede modificar ambos niveles con ayuda de 3 botoes, 2 para subir y bajar y un 3 para elegir que nivel se va a modificar.]

## Estructura del repositorio
```
Practica_X
├── img/            # Esquemáticos y fotos del prototipo
├── src/
│   └── main.cpp
├── docs/
│   └── reporte.pdf
├── diagram.json
├── platformio.ini
├── wokwi.toml
└── README.md
```

## Cómo ejecutarlo
1. Clona el repositorio.
2. Ábrelo en VS Code con PlatformIO.
3. Compila y sube el código, o simula con Wokwi usando `diagram.json`.

