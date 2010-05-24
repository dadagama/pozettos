<?php 
/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/

session_start();

require_once("../modulo_estadistica/Estadistica.inc");
$objetoEstadistica = new Estadistica($_SESSION['arregloParametros']);

switch($_REQUEST['accion'])
{	
	case "mostrarModulo":
		require_once("../modulo_".$_REQUEST['nombre_modulo']."/fm_".$_REQUEST['nombre_modulo'].".php");
		break;
	
	case "cargarCategorias":
		$objetoEstadistica->cargarCategorias();
		break;
	
	case "actualizarEstadisticas":
		echo $objetoEstadistica->actualizarEstadisticas($_REQUEST['hiv_id']);
		break;
}
?>