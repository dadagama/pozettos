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
	url_controlador_modulo = "../modulo_deuda/deuda.php";
	actualizarHistorialDeudas();
	$("#tbl_historial").tablesorter({widgets: ['zebra']});
}

function actualizarOrdenamiento()
{
  $("#tbl_historial").trigger("update");
  var sorting = [[1,0],[8,0],[2,0]];
  $("#tbl_historial").trigger("sorton",[sorting]); 
}

function editableObservacion(fila_id,editable)
{
  if(editable)
  {
    var hiv_observacion = $('#'+fila_id).children().text();
    var input_observacion = "<input type='text' class='ancho_90p verdana letra_9' onBlur='if(actualizarValor(\""+fila_id+"\",\"hiv_observacion\",13)){ editableObservacion(\""+fila_id+"\",false);}' onKeypress='if(actualizarValor(\""+fila_id+"\",\"hiv_observacion\",event.keyCode)){ editableObservacion(\""+fila_id+"\",false);}' value='"+hiv_observacion+"'/>";
    $('#'+fila_id).children().replaceWith(input_observacion);
    $('#'+fila_id).children().focus();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editableObservacion(\"'+fila_id+'\",true);');
    var hiv_observacion = $('#'+fila_id).children().val();
    if(hiv_observacion == undefined)
      hiv_observacion = "";
    var label_observacion = "<label class='cursor_cruz'>"+hiv_observacion+"</label>";
    $('#'+fila_id).children().replaceWith(label_observacion);
  }
}

function actualizarValor(fila_id,nombre_campo, evento)
{
  if(evento == 13)
  {
    var arreglo_id = fila_id.split("_");
    var hiv_id = arreglo_id[(arreglo_id.length - 1)];
    var valor_nuevo = $('#'+fila_id).children().val();
    if(valor_nuevo == undefined)
      valor_nuevo = "";
    ajax('accion=actualizarValor&hiv_id='+hiv_id+"&valor_nuevo="+valor_nuevo+"&nombre_campo="+nombre_campo, false, actualizarAjax, false);
    return true;
  }
  else
    return false;
}

function actualizarAjax(actualizo)
{
  if(actualizo)
  {
    console.log("actualizado!");
    actualizarOrdenamiento();
  }
  else
    console.log("no se actualizo ningun valor de la fila");
}

function actualizarEstadoPago(id_fila, ultimo_clic)
{
	if(mensajeConfirmar())
	{
		var hiv_pago = $('#hiv_chk_pago_'+id_fila).attr('checked');
		var hiv_es_tiempo_gratis = $('#hiv_chk_gratis_'+id_fila).attr('checked');
		ajax("accion=actualizarEstadoPago&id_fila="+id_fila+"&hiv_pago="+hiv_pago+"&hiv_es_tiempo_gratis="+hiv_es_tiempo_gratis+"&ultimo_clic="+ultimo_clic, null, actualizarEstadoPagoAjax, null);
	}
	else
	{
		$('#hiv_chk_pago_'+id_fila).removeAttr('checked');
		$('#hiv_chk_gratis_'+id_fila).removeAttr('checked');
	}
}

function actualizarEstadoPagoAjax(id_actualizado)
{
	if(id_actualizado)
	{
	  $("#hiv_fila_"+id_actualizado).remove();
    actualizarOrdenamiento();
  }  
	else
		console.log('Error actualizando estado del pago');
}

function actualizarHistorialDeudas()
{
	ajax("accion=actualizarHistorialDeudas", null, actualizarHistorialDeudasAjax, null);
}

function actualizarHistorialDeudasAjax(info_servicios)
{
	$("#historial_deudas").children().remove();
	$("#historial_deudas").html(info_servicios);
	actualizarOrdenamiento();
}