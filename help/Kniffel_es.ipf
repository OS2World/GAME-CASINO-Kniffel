.* Ayuda de Kniffel - Espanol
:userdoc.

:h1 res=001.Ayuda general
:font facename=Helv size=8x12.
:p.
Kniffel es el juego de dados conocido como Yahtzee, para uno a cinco jugadores. Elija un tema&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Iniciar un juego:elink.
:li.:link reftype=hd res=003.Nombres y simbolos de los jugadores:elink.
:li.:link reftype=hd res=004.Jugar:elink.
:li.:link reftype=hd res=005.Las reglas:elink.
:li.:link reftype=hd res=006.Resultados y mejores resultados:elink.
:li.:link reftype=hd res=007.Teclas:elink.
:li.:link reftype=hd res=008.Menus y opciones:elink.
:li.:link reftype=hd res=009.Acerca de Kniffel y licencia:elink.
:eul.
:p.

:h1 res=002.Iniciar un juego
:font facename=Helv size=8x12.
:p.
Elija :hp2.Juego - Nuevo juego:ehp2. (Ctrl+N). En la ventana Nuevo juego seleccione el numero de jugadores, de uno a cinco, e introduzca el nombre y el simbolo de cada jugador.
:p.
:hp2.Jugar:ehp2. inicia el juego. :hp2.Mejores resultados:ehp2. muestra los resultados guardados de juegos anteriores; el boton solo esta disponible si hay resultados guardados. :hp2.Cerrar:ehp2. cierra la ventana.

:h1 res=003.Nombres y simbolos de los jugadores
:font facename=Helv size=8x12.
:p.
Cada jugador escribe un nombre de hasta 12 caracteres y elige un simbolo. El nombre propuesto esta marcado, asi que la primera tecla que pulse lo sustituye.
:p.
Con los dos botones de flecha junto al simbolo puede recorrer los simbolos. Los simbolos son los iconos de la carpeta :hp2.icons:ehp2. junto a Kniffel.exe. Si hay menos de cinco, el programa anade algunos propios. A los ninos les gusta reconocerse por un simbolo favorito, asi que puede copiar mas iconos a la carpeta.

:h1 res=004.Jugar
:font facename=Helv size=8x12.
:p.
La ventana muestra una linea de informacion, los cinco dados, los botones de mando a la derecha y la tabla de puntos abajo, con una columna por jugador. La columna del jugador al que le toca tiene el encabezado amarillo.
:p.
:dl tsize=18.
:dt.:hp2.Tirar:ehp2.
:dd.Tira todos los dados que no estan retenidos. Un jugador puede tirar tres veces por turno.
:dt.Pulsar un dado
:dd.Retiene el dado (se muestra invertido) o lo suelta otra vez. Los dados retenidos no se tiran.
:dt.:hp2.Invertir todos:ehp2.
:dd.Retiene todos los dados libres y suelta todos los retenidos.
:dt.Pulsar un campo libre
:dd.Anota los puntos de los dados actuales en ese campo de la tabla. Es posible despues de la primera tirada.
:dt.:hp2.Deshacer:ehp2.
:dd.Anula la anotacion mientras no se haya pulsado Siguiente jugador. Despues ya no se puede tirar.
:dt.:hp2.Siguiente jugador:ehp2.
:dd.Pasa el turno al siguiente jugador.
:dt.:hp2.Abandonar:ehp2.
:dd.Termina el juego sin resultado y vuelve al inicio.
:edl.

:h1 res=005.Las reglas
:font facename=Helv size=8x12.
:p.
Cada jugador rellena los 13 campos de la tabla, uno por turno.
:ul compact.
:li.Unos a Seises&colon. se necesitan al menos tres dados iguales; solo cuentan los dados iguales, si no el campo recibe cero.
:li.Bonus&colon. una suma de 63 o mas en la seccion superior anade 35 puntos. El campo de suma muestra un signo menos hasta alcanzar 63.
:li.Trio y Poker&colon. se necesitan tres o cuatro dados iguales; entonces cuentan los cinco dados.
:li.Full&colon. tres dados iguales y una pareja, 25 puntos.
:li.Escalera menor&colon. cuatro numeros seguidos, 30 puntos.
:li.Escalera mayor&colon. cinco numeros seguidos (12345 o 23456), 40 puntos.
:li.Kniffel&colon. cinco dados iguales, 50 puntos.
:li.Chance&colon. cualquier dado, cuentan los cinco.
:eul.
:p.
Gana el jugador con el total mas alto.

:h1 res=006.Resultados y mejores resultados
:font facename=Helv size=8x12.
:p.
Cuando todos los campos de todos los jugadores estan rellenos, se muestra el resultado con el ganador y los demas. :hp2.Guardar resultado:ehp2. anade el resultado al archivo :hp2.hitlist.hgh:ehp2. del directorio de trabajo. :hp2.Jugar de nuevo:ehp2. empieza un juego nuevo con los mismos jugadores, :hp2.Volver:ehp2. regresa al inicio.
:p.
:hp2.Juego - Mejores resultados:ehp2. (Ctrl+H) muestra los resultados guardados. Con :hp2.Borrar lista:ehp2. se elimina el archivo tras una confirmacion.

:h1 res=007.Teclas
:font facename=Helv size=8x12.
:p.
:parml compact tsize=14 break=none.
:pt.Espacio
:pd.Tirar
:pt.1 a 5
:pd.Retener / soltar el dado 1 a 5
:pt.I
:pd.Invertir todos
:pt.Intro
:pd.Siguiente jugador
:pt.Retroceso
:pd.Deshacer
:pt.Ctrl+N
:pd.Nuevo juego
:pt.Ctrl+Q
:pd.Abandonar el juego actual
:pt.Ctrl+H
:pd.Mejores resultados
:pt.Ctrl+B
:pd.Botones con imagen si / no
:pt.Ctrl+F
:pd.Controles de marco si / no
:pt.Ctrl+X
:pd.Salir
:eparml.

:h1 res=008.Menus y opciones
:font facename=Helv size=8x12.
:p.
:dl tsize=18.
:dt.:hp2.Juego:ehp2.
:dd.Nuevo juego, Abandonar juego (termina el juego sin resultado), Mejores resultados y Salir.
:dt.:hp2.Botones con imagen:ehp2.
:dd.Muestra imagenes en lugar de texto en los botones y en la tabla. Las imagenes son ideales para ninos pequenos.
:dt.:hp2.Idioma:ehp2.
:dd.Ingles, espanol, neerlandes, aleman, frances o italiano. Menus, ventanas, dialogos y esta ayuda cambian al instante.
:dt.:hp2.Controles de marco:ehp2. (Ctrl+F)
:dd.Oculta o muestra la barra de titulo y el menu.
:dt.:hp2.Guardar al salir:ehp2.
:dd.Guarda la configuracion en Kniffel.cfg al salir.
:edl.

:h1 res=009.Acerca de Kniffel y licencia
:font facename=Helv size=8x12.
:p.
Kniffel fue escrito para OS/2 en VisPro/REXX por Andreas Kieser entre 1996 y 1999 y publicado como freeware. La version en C para Open Watcom fue preparada por la comunidad OS2World en 2026.
:p.
Kniffel es software libre&colon. puede redistribuirlo y/o modificarlo bajo los terminos de la Licencia Publica General de GNU publicada por la Free Software Foundation, ya sea la version 3 de la Licencia o (a su eleccion) cualquier version posterior. Se distribuye con la esperanza de que sea util, pero SIN NINGUNA GARANTIA. Vea el archivo LICENSE.txt.

:euserdoc.
