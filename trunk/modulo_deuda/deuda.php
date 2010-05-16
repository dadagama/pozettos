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

require_once("../modulo_deuda/Deuda.inc");
$objetoDeuda = new Deuda($_SESSION['arregloParametros']);

switch($_REQUEST['accion'])
{
	case "actualizarListaClientes":
		echo $objetoDeuda->actualizarListaClientes(trim($_REQUEST['info_cliente']));
		break;
	
	case "actualizarHistoricoProductos":
		$objetoDeuda->actualizarHistoricoProductos($_REQUEST['cli_id']);
		break;
		
	case "actualizarHistoricoServicios":
		$objetoDeuda->actualizarHistoricoServicios($_REQUEST['cli_id']);
		break;

	case "actualizarEstadoDeuda":
		//se retorna el prefijo de la zona de actualizacion
		echo $objetoDeuda->actualizarEstadoDeuda($_REQUEST['prefijo'], $_REQUEST['id_fila'], $_REQUEST['estado']);
		break;
		
	case "actualizarObservacion":
		$objetoDeuda->actualizarObservacion($_REQUEST['prefijo'], $_REQUEST['id_fila'], $_REQUEST['observacion']);
		break;
}
?>