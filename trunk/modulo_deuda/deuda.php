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
	case "mostrarPanel":
		require_once("../modulo_panel/fm_panel.php");
		break;
	
	case "actualizarValor":
		echo $objetoDeuda->actualizarValor($_REQUEST['hiv_id'],$_REQUEST['valor_nuevo'],$_REQUEST['nombre_campo']);
		break;

	case "actualizarEstadoPago":
		if($objetoDeuda->actualizarEstadoPago($_REQUEST['id_fila'], $_REQUEST['hiv_pago'], $_REQUEST['hiv_es_tiempo_gratis'], $_REQUEST['ultimo_clic']))
			$objetoDeuda->actualizarHistorialVentas();
		else
			echo false;
		break;
		
	case "actualizarHistorialDeudas":
		$objetoDeuda->actualizarHistorialDeudas();
		break;
}
?>