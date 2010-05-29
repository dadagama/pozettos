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

switch($_REQUEST['accion'])
{
	case "mostrarModulo":
		require_once("../modulo_".$_REQUEST['nombre_modulo']."/fm_".$_REQUEST['nombre_modulo'].".php");
		break;
		
	/*case "mostrarContabilidad":
		require_once("../modulo_contabilidad/fm_contabilidad.php");
		break;
		
	case "mostrarDeudores":
		require_once("../modulo_deuda/fm_deuda.php");
		break;*/
}
?>