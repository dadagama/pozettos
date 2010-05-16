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

require_once("../modulo_contabilidad/Contabilidad.inc");
$objetoContabilidad = new Contabilidad($_SESSION['arregloParametros'], $_SESSION['fecha_contabilidad']);

switch($_REQUEST['accion'])
{	
/**********************************
******* ACCIONES GENERICAS  *******
***********************************/
	
	case "mostrarPanel":
		require_once("../modulo_panel/fm_panel.php");
		break;
	
	case "actualizarListaClientes":
		echo $objetoContabilidad->actualizarListaClientes(trim($_REQUEST['info_cliente']));
		break;
		
	case "actualizarCampoColor":
		$prefijo = $_REQUEST['prefijo'];
		echo $objetoContabilidad->actualizarCampoColor($_REQUEST[$prefijo.'_id'],$_REQUEST[$prefijo.'_color_fila'], $prefijo);
		break;
		
	case "actualizarEstadoDeuda":
		//se retorna el prefijo de la zona de actualizacion
		echo $objetoContabilidad->actualizarEstadoDeuda($_REQUEST['prefijo'], $_REQUEST['id_fila'], $_REQUEST['estado']);
		break;
	
	case "eliminarFila":
		//se retorna el id de la fila eliminada
		echo $objetoContabilidad->eliminarFila($_REQUEST['id'], $_REQUEST['prefijo']);
		break;
		
	case "actualizarObservacion":
		$objetoContabilidad->actualizarObservacion($_REQUEST['prefijo'], $_REQUEST['id_fila'], $_REQUEST['observacion']);
		break;
		
/**********************************
******* ACCIONES PRODUCTOS  *******
***********************************/

	case "agregarFilaProducto":
		echo $objetoContabilidad->agregarFilaProducto($_REQUEST['vep_cli_id'], 
																									$_REQUEST['vep_pro_id'],
																									$_REQUEST['vep_total'],
																									$_REQUEST['vep_fecha_venta']);
		break;
	
	case "actualizarHistoricoProductos":
		$objetoContabilidad->actualizarHistoricoProductos();
		break;
		
/**********************************
******* ACCIONES SERVICIOS  *******
***********************************/

	case "agregarFilaServicio":
		$objetoContabilidad->agregarFilaServicio($_REQUEST['ves_ser_id'],
																							$_REQUEST['ves_hora'],
																							$_REQUEST['ves_minuto'],
																							$_REQUEST['ves_meridiano'],
																							$_REQUEST['ves_duracion'],
																							$_REQUEST['ves_total'],
																							$_REQUEST['ves_cli_id'],
																							$_REQUEST['ves_fecha']);
		break;
	
	case "actualizarHistoricoServicios":
		$objetoContabilidad->actualizarHistoricoServicios();
		break;
		
	case "actualizarTotalServicio":
		echo $objetoContabilidad->actualizarTotalServicio($_REQUEST['servicio'],$_REQUEST['duracion']);
		break;
		
	case "actualizarDuracionYTotalServicio":
		echo $objetoContabilidad->actualizarDuracionYTotalServicio($_REQUEST['id'],$_REQUEST['duracion']);
		break;

/**********************************
******* ACCIONES TIMERS     *******
***********************************/

	case "obtenerInfoTimers":
		echo json_encode($objetoContabilidad->obtenerInfoTimers());
		break;
}
?>