<?php
/*
 This file is part of Pozzettos.

    Pozzettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozzettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozzettos.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * Interfaz para estandarizar las conexiones a fuentes externas.
 * @author	dadagama
 * @since	07-03-2009
 * @version	1.0
 */
abstract class Conexion
{
  /**
   * Arreglo asociativo que almacena los datos necesarios para realizar esta 
   * conexión con la fuente externa. estos son los posibles valores:<br/>
   * --- Para conexion con BD ---<br/>
   * ['con_servidor']	=> string<br/>
   * ['con_usuario']	=> string<br/>
   * ['con_password']	=> string<br/>
   * ['con_nombre_bd']	=> string
   * @var	array
   */
  var $_parametrosConexion;
  
  /**
   * Efectua esta conexión con la fuente externa.
   * @return	boolean	Verdadero si logra conectar, Falso en caso 
   * 					contrario.
   */
  abstract function conectar();
  
  /**
   * Termina esta conexión con la fuente externa.
   * @return	boolean	Verdadero si logra desconectar, Falso en caso contrario.
   */
  abstract function desconectar();
  
  /**
   * Retorna el arreglo que contiene los datos necesarios para realizar esta
   * conexión con la fuente externa.
   * @return	array
   */
  abstract function obtenerParametrosConexion();
}
?>
