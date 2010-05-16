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

require_once("ConexionBD.inc");
class ConexionBDMySQL extends ConexionBD
{
  function __construct($arregloParametros)
  {
	 $this->_parametrosConexion = $arregloParametros;
  }
  
  function conectar()
  {
		$servidor = $this->_parametrosConexion['con_servidor'];
		$usuario  = $this->_parametrosConexion['con_usuario'];
		$clave    = $this->_parametrosConexion['con_password'];
		$bd       = $this->_parametrosConexion['con_nombre_bd'];

		if($this->_conexion = mysql_connect($servidor, $usuario, $clave, true))
			return $this->establecer_bd($bd);
		else
			return false;
  }
  
	function establecer_bd($bd)
	{
		return mysql_select_db($bd, $this->_conexion);
	}
	
  function desconectar()
  {
		return mysql_close($this->_conexion);
  }
  
	function obtenerParametrosConexion()
  {
		return $this->_parametrosConexion;
  }
	
	function obtener_error()
	{
		return mysql_error($this->_conexion);
	}
  
  function ejecutarSQL($instruccionSQL)
  {
		$this->_resultSet = mysql_query($instruccionSQL, $this->_conexion);
  }
  
  function obtenerResultadoComoArregloAsociativo()
  {
		$arreglo = array();
		while ($row = $this->obtenerFilaComoArregloAsociativo()) 
		{
			$arreglo[] = $row;
		}
		return $arreglo;
  }

	function obtenerNumeroFilas()
	{
		return mysql_num_rows($this->_resultSet);
	}
	
	function obtenerResultset()
	{
		return $this->_resultSet;
	}
	
	function obtenerFilaComoArregloAsociativo()
	{
		if($fila = mysql_fetch_assoc($this->_resultSet))
			return $fila;
		else 
			return false;
	}
	
	function obtenerFilaComoArreglo()
	{
		if($fila = mysql_fetch_array($this->_resultSet))
			return $fila;
		else 
			return false;
	}
  
	function obtenerFilaComoCadena()
	{
		$row = mysql_fetch_row($this->_resultSet);
		return implode(",", $row);
	}
	
	function existeRegistro($campos, $tablas, $condiciones)
	{
		$sql = "SELECT $campos FROM $tablas WHERE $condiciones";
		$this->ejecutarSQL($sql);
		return $this->obtenerNumeroFilas();
	}
	
	function obtenerNumeroFilasAfectadas()
	{
		return mysql_affected_rows($this->_conexion);
	}
}
?>
