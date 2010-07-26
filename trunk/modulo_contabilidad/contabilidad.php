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
	case "mostrarModulo":
    $viene_de_icono = true;
		require_once("../modulo_".$_REQUEST['nombre_modulo']."/fm_".$_REQUEST['nombre_modulo'].".php");
		break;
	
	case "obtenerOptions":
		echo $objetoContabilidad->obtenerOptions();
		break;

	case "cargarSaldoInicialTitan":
		echo $objetoContabilidad->cargarSaldoInicialTitan($_REQUEST['sit_fecha']);
		break;
	
  case "actualizarSaldoBase":
		echo $objetoContabilidad->actualizarSaldoBase($_REQUEST['bas_saldo'], $_REQUEST['bas_fecha']);
		break;
    
	case "actualizarSaldoTitan":
		echo $objetoContabilidad->actualizarSaldoTitan($_REQUEST['sit_saldo'], $_REQUEST['sit_fecha']);
		break;
	
	case "actualizarSaldoEgresos":
		echo $objetoContabilidad->actualizarSaldoEgresos($_REQUEST['egd_saldo'], $_REQUEST['egd_fecha']);
		break;
	
	case "actualizarDeudaCliente":
			$objetoContabilidad->actualizarValor($_REQUEST['hiv_id'],$_REQUEST['valor_nuevo'],"hiv_cli_id");
			//$valor_nuevo tiene el id del nuevo cliente y puedo consultar la deuda
			//de este cliente para actualizar la imagen de deuda
			echo "{hiv_id:'".$_REQUEST['hiv_id']."', valor_deuda:'".$objetoContabilidad->actualizarDeudaCliente($_REQUEST['valor_nuevo'])."'}";
		break;
		
	case "actualizarValor":
		echo $objetoContabilidad->actualizarValor($_REQUEST['hiv_id'],$_REQUEST['valor_nuevo'],$_REQUEST['nombre_campo']);
		break;
		
	case "actualizarInicio":
		$objetoContabilidad->actualizarValor($_REQUEST['hiv_id'],$_REQUEST['valor_nuevo'],"hiv_hora");
		echo $objetoContabilidad->obtenerJsonHoras($_REQUEST['hiv_id']);
		break;
		
	case "actualizarDuracion":
		$objetoContabilidad->actualizarValor($_REQUEST['hiv_id'],$_REQUEST['valor_nuevo'],"hiv_dus_minutos");
		$objetoContabilidad->actualizarTotal($_REQUEST['hiv_id']);
		echo $objetoContabilidad->obtenerJsonHoras($_REQUEST['hiv_id']);
		break;

	case "actualizarCampoColor":
		echo $objetoContabilidad->actualizarCampoColor($_REQUEST['hiv_id'],$_REQUEST['hiv_color_fila']);
		break;

	case "actualizarEstadoPago":
		echo $objetoContabilidad->actualizarEstadoPago($_REQUEST['id_fila'], $_REQUEST['hiv_pago'], $_REQUEST['hiv_es_tiempo_gratis'], $_REQUEST['ultimo_clic']);
		break;
		
	case "eliminarFila":
		// se retorna el id de la fila eliminada
		echo $objetoContabilidad->eliminarFila($_REQUEST['id']);
		break;

/**********************************
******* ACCIONES HISTORIAL  *******
***********************************/

	case "agregarFilaHistorial":
		echo $objetoContabilidad->agregarFilaHistorial($_REQUEST['hiv_ser_id'],
      																							$_REQUEST['hiv_ser_tipo'],
      																							$_REQUEST['hiv_hora'],
      																							$_REQUEST['hiv_minuto'],
      																							$_REQUEST['hiv_meridiano'],
      																							$_REQUEST['hiv_dus_minutos'],
      																							$_REQUEST['hiv_total'],
      																							$_REQUEST['hiv_fecha']);
		break;
	
	case "actualizarHistorialVentas":
		echo $objetoContabilidad->actualizarHistorialVentas();
		break;
/**********************************
******* ACCIONES TIMERS     *******
***********************************/
/*
	case "obtenerInfoTimers":
		echo json_encode($objetoContabilidad->obtenerInfoTimers());
		break;
*/
}
?>