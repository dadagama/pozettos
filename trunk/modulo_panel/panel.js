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
$(document).ready(inicializar);

function inicializar()
{
	url_controlador_modulo = "panel.php";
	$('#con_fecha').datepicker({  dateFormat: 'yy-mm-dd',
                                onSelect: function(dateText, inst){ 
                                  ajax('accion=mostrarModulo&nombre_modulo=contabilidad&con_fecha='+$("#con_fecha").val(), false, mostrarNuevoModulo_ajax, false); 
                                }
                              });
}