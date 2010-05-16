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

require_once("Conexion.inc");
/**
 * Interfaz para estandarizar las conexiones a Bases de datos.
 * @author	dadagama
 * @since	07-03-2009
 * @version	1.0
 */
abstract class ConexionBD extends Conexion
{
  /**
   * Almacena el resulset arrojado por una instrucción sql.
   * @var	source
   */
  var $_resultSet;
  
  /**
   * Almacena la instrucción sql en forma de cadena.
   * @var	string
   */
  var $_sql;
  
  /**
   * Almacena un objeto de conexión. 
   * @var	link
   */
  var $_conexion;
  
	/**
   * Retorna el error devuelto en un resulset.
   * @return	string	Error devuelto por ejecutar una consulta erronea.
   */
	abstract function obtener_error();
  
  /**
   * Ejecuta la instrucción sql en la base de datos 
   * y guarda el resultado en la variable _resultSet de la clase.
   * @param		$sql	Instrucción sql a ejecutar.
   * @return	resource|boolean	Para SELECT, SHOW, DESCRIBE y EXPLAIN 
	 * 														retorna un resultset que se asigna a la 
	 * 														variable _resultSet de la clase ó Falso en 
	 * 														caso de error. Para INSERT, UPDATE, DELETE y 
	 * 														DROP retorna Verdadero si es satisfactoria ó 
	 * 														Falso en caso de error.
   * @see		obtenerResultadoComoArreglo()
   */
  abstract function ejecutarSQL($sql);
  
  /**
   * Transforma el resulset de la clase en un arreglo simple que contiene 
	 * arreglos asociativos y lo retorna.
   * El resulset de la clase se debe encontrar inicializado antes de hacer el 
   * llamado a esta función.
   * @return 	array	Arreglo simple que contiene arreglos asociativos.<br/>
										[0] => array("campo 1" => "valor 1", "campo 2" => "valor N")
										[1] => array("campo 1" => "valor 1", "campo 2" => "valor N")
										[M] => array("campo 1" => "valor 1", "campo 2" => "valor N")
   */
  abstract function obtenerResultadoComoArregloAsociativo();
  
  /**
   * Retorna el numero de filas del resulset devuelto por una sentencia SELECT
   * ó SHOW.
   * @return	int	Numero de filas almacenadas en el resultset.
   */
  abstract function obtenerNumeroFilas();  
  
	/**
   * retorna el objeto _resulset de la clase.
   * @return	
   */ 
	abstract function obtenerResultset();
	
	/**
   * retorna un registro del _resulset como arreglo asociativo, donde los 
	 * indices del arreglo con los nombres de los campos consultados.
   * @return	array	arreglo asociativo con un registro del resultset.<br/>
										["campo 1"] => "valor 1"<br/>
										["campo 2"] => "valor 2"<br/>
										["campo N"] => "valor N"<br/>
   */ 
	abstract function obtenerFilaComoArregloAsociativo();
	
	/**
   * retorna un registro del _resulset como arreglo simple, donde los 
	 * indices del arreglo son numéricos.
   * @return	array	arreglo simple con un registro del resultset.<br/>
										[0] => "valor 1"<br/>
										[1] => "valor 2"<br/>
										[2] => "valor N"<br/>
   */ 
	abstract function obtenerFilaComoArreglo();
  
	/**
   * retorna un registro del _resulset como una cadena, donde se separan los
	 * campos por comas (,).
   * @return	string	cadena que representa un registro separado por comas.<br/>
											valor1,valor2,valorN
   */ 
	abstract function obtenerFilaComoCadena();
	
	/**
   * retorna true si existe el registro en la tabla. false en caso contrario.
   * @return	boolean	bandera que indica si el registro existe previamente en la
											tabla.
   */ 
	abstract function existeRegistro($campos, $tablas, $condiciones);
  
}
?>
