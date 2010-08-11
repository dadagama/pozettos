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
	url_controlador_modulo = "../modulo_cliente/cliente.php";
  actualizarListaClientes();
}

function actualizarListaClientes()
{
  ajax("accion=actualizarListaClientes", null, actualizarListaClientesAjax, null);
}

function actualizarListaClientesAjax(info_clientes)
{
  $("#tbody_clientes").children().remove();
  $("#tbody_clientes").html(info_clientes);
  $("#tbl_clientes").tablesorter({widgets: ['zebra']});
  $("#tbl_clientes").trigger("update");
  var sorting = [[1,0]];
  $("#tbl_clientes").trigger("sorton",[sorting]);
}

function agregarCliente()
{
  var cli_nombre = $("#cli_nombre").val();
  var cli_apellido = $("#cli_apellido").val();
  var cli_email = $("#cli_email").val();
  ajax("accion=agregarCliente&cli_nombre="+cli_nombre+"&cli_apellido="+cli_apellido+"&cli_email="+cli_email, null, agregarClienteAjax, null);
}

function agregarClienteAjax(info_cliente)
{
  if(info_cliente)
  {
    $("#tbody_clientes").append(info_cliente);
    $("#tbl_clientes").trigger("update"); 
    alert("Se agrego un cliente correctamente");
  }
  else
    console.log('Error al registrar el cliente');
}

function editarCampo(fila_id,editable)
{
  if(editable)
  {
    var texto_campo = $('#'+fila_id).children().text();
    var arreglo_id = fila_id.split("_");
    var nombre_campo = fila_id.substring(0,fila_id.lastIndexOf('_'));
    var input_campo = "<input type='text' class='ancho_100p verdana letra_9' onBlur='if(actualizarValor(\""+fila_id+"\",\""+nombre_campo+"\",13)){ editarCampo(\""+fila_id+"\",false);}' onKeypress='if(actualizarValor(\""+fila_id+"\",\""+nombre_campo+"\",event.keyCode)){ editarCampo(\""+fila_id+"\",false);}' value='"+texto_campo+"'/>";
    $('#'+fila_id).children().replaceWith(input_campo);
    $('#'+fila_id).children().focus();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editarCampo(\"'+fila_id+'\",true);');
    var valor_campo = $('#'+fila_id).children().val();
    var label_campo = "<label class='cursor_cruz'>"+valor_campo+"</label>";
    $('#'+fila_id).children().replaceWith(label_campo);
  }
}

function actualizarValor(fila_id,nombre_campo, evento)
{
  if(evento == 13)
  {
    var arreglo_id = fila_id.split("_");
    var cli_id = arreglo_id[(arreglo_id.length - 1)];
    var valor_nuevo = $('#'+fila_id).children().val();
    if(valor_nuevo == undefined)
      valor_nuevo = "";
    ajax('accion=actualizarValor&cli_id='+cli_id+"&valor_nuevo="+valor_nuevo+"&nombre_campo="+nombre_campo, false, actualizarValorAjax, false);
    return true;
  }
  else
    return false;
}

function actualizarValorAjax(actualizo)
{
  if(actualizo)
    console.log("actualizado!");
  else
    console.log("no se actualizo ningun valor de la fila");
}