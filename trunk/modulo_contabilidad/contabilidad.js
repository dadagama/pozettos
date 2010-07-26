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

var options_clientes;
var options_duracion;

function inicializar()
{
  url_controlador_modulo = "../modulo_contabilidad/contabilidad.php";
  options_clientes = "";
  options_duracion = "";
  obtenerOptions();

  $("#tbl_historial").tablesorter({ headers: {
                                              0: {sorter: 'text' },
                                              1: {sorter: 'digit' },
                                              2: {sorter: false },
                                              3: {sorter: false },
                                              4: {sorter: false },
                                              5: {sorter: false },
                                              6: {sorter: false },
                                              7: {sorter: false },
                                              8: {sorter: false },
                                              9: {sorter: false },
                                              10: {sorter: false },
                                              11: {sorter: false },
                                              12: {sorter: false },
                                              13: {sorter: false }
                                            },
                                    widgets: ['zebra']
                                  });
  actualizarHistorialVentas();
  /*obtenerInfoTimers();*/
}

function obtenerOptions()
{
  ajax('accion=obtenerOptions', false, obtenerOptionsAjax, false);
}

function obtenerOptionsAjax(jsonOptions)
{
  var obj_options = eval("("+jsonOptions+")");
  options_clientes = obj_options.options_clientes;
  options_duracion = obj_options.options_duracion;
  //evitar un llamado adicional de ajax para obtener saldo inicial titan
  $("#sit_saldo").text(obj_options.sit_saldo);
  $("#egd_saldo").text(obj_options.egd_saldo);
  $("#bas_saldo").text(obj_options.bas_saldo);
}

function actualizarOrdenamiento()
{
  $("#tbl_historial").trigger("update");
  var sorting = [[0,1],[1,1]];
  $("#tbl_historial").trigger("sorton",[sorting]); 
}

function editableSaldoBase(editable)
{
  if(editable)
  {
    var bas_saldo = $('#bas_saldo').text();
    var input_saldo = "<input id='bas_saldo' type='text' maxlength='7' class='ancho_55 verdana' onBlur='if(actualizarSaldoBase(13)){ editableSaldoBase(false);}' onKeypress='if(actualizarSaldoBase(event.keyCode)){ editableSaldoBase(false);}' value='"+bas_saldo+"'/>";
    $('#bas_saldo').replaceWith(input_saldo);
    $('#bas_saldo').select();
  }
  else
  {
    var valor_saldo = $('#bas_saldo').val();
    var bas_saldo = parseInt(valor_saldo.replace(".", ""));
    if(bas_saldo == "" || isNaN(bas_saldo))
      bas_saldo = "0";
    var label_saldo = "<label id='bas_saldo' ondblclick='editableSaldoBase(true);' class='verdana letra_9 cursor_cruz'>"+bas_saldo+"</label>";
    $('#bas_saldo').replaceWith(label_saldo);
  }
}

function actualizarSaldoBase(evento)
{
  if(evento == 13)
  {
    var valor_saldo = $('#bas_saldo').val();
    var bas_saldo = parseInt(valor_saldo.replace(".", ""));
    var bas_fecha = $("#fecha_contabilidad").val();
    ajax('accion=actualizarSaldoBase&bas_saldo='+bas_saldo+"&bas_fecha="+bas_fecha, false, actualizarAjax, false);
    return true;
  }
  else
    return false;
}

function editableSaldoTitan(editable)
{
  if(editable)
  {
    var sit_saldo = $('#sit_saldo').text();
    var input_saldo = "<input id='sit_saldo' type='text' maxlength='7' class='ancho_55 verdana' onBlur='if(actualizarSaldoTitan(13)){ editableSaldoTitan(false);}' onKeypress='if(actualizarSaldoTitan(event.keyCode)){ editableSaldoTitan(false);}' value='"+sit_saldo+"'/>";
    $('#sit_saldo').replaceWith(input_saldo);
    $('#sit_saldo').select();
  }
  else
  {
    var valor_saldo = $('#sit_saldo').val();
    var sit_saldo = parseInt(valor_saldo.replace(".", ""));
    if(sit_saldo == "" || isNaN(sit_saldo))
      sit_saldo = "0";
    var label_saldo = "<label id='sit_saldo' ondblclick='editableSaldoTitan(true);' class='verdana letra_9 cursor_cruz'>"+sit_saldo+"</label>";
    $('#sit_saldo').replaceWith(label_saldo);
  }
}

function actualizarSaldoTitan(evento)
{
  if(evento == 13)
  {
    var valor_saldo = $('#sit_saldo').val();
    var sit_saldo = parseInt(valor_saldo.replace(".", ""));
    var sit_fecha = $("#fecha_contabilidad").val();
    ajax('accion=actualizarSaldoTitan&sit_saldo='+sit_saldo+"&sit_fecha="+sit_fecha, false, actualizarAjax, false);
    return true;
  }
  else
    return false;
}

function editableSaldoEgresos(editable)
{
  if(editable)
  {
    var egd_saldo = $('#egd_saldo').text();
    var input_saldo = "<input id='egd_saldo' type='text' maxlength='7' class='ancho_55 verdana' onBlur='if(actualizarSaldoEgresos(13)){ editableSaldoEgresos(false);}' onKeypress='if(actualizarSaldoEgresos(event.keyCode)){ editableSaldoEgresos(false);}' value='"+egd_saldo+"'/>";
    $('#egd_saldo').replaceWith(input_saldo);
    $('#egd_saldo').select();
  }
  else
  {
    var valor_saldo = $('#egd_saldo').val();
    var egd_saldo = parseInt(valor_saldo.replace(".", ""));
    if(egd_saldo == "" || isNaN(egd_saldo))
      egd_saldo = "0";
    var label_saldo = "<label id='egd_saldo' ondblclick='editableSaldoEgresos(true);' class='verdana letra_9 cursor_cruz'>"+egd_saldo+"</label>";
    $('#egd_saldo').replaceWith(label_saldo);
  }
}

function actualizarSaldoEgresos(evento)
{
  if(evento == 13)
  {
    var valor_saldo = $('#egd_saldo').val();
    var egd_saldo = parseInt(valor_saldo.replace(".", ""));
    var egd_fecha = $("#fecha_contabilidad").val();
    ajax('accion=actualizarSaldoEgresos&egd_saldo='+egd_saldo+"&egd_fecha="+egd_fecha, false, actualizarAjax, false);
    return true;
  }
  else
    return false;
}

function editableCliente(fila_id,editable)
{
  if(editable)
  {
    var cli_id = $('#'+fila_id).children("label").text();
    var select_clientes = "<select class='ancho_55' onchange='if(actualizarDeudaCliente(\""+fila_id+"\",13)){ editableCliente(\""+fila_id+"\",false);}' onBlur='if(actualizarDeudaCliente(\""+fila_id+"\",13)){ editableCliente(\""+fila_id+"\",false);}'>";
    select_clientes += options_clientes;
    select_clientes += "</select>";
    $('#'+fila_id+' label').replaceWith(select_clientes);
    $('#'+fila_id+' select').removeAttr('selected', 'selected');
    $('#'+fila_id+' select option[value="'+cli_id+'"]').attr('selected', 'selected');
    $('#'+fila_id+' select').focus();
  }
  else
  {
    var nombre_cliente = $('#'+fila_id+' select option:selected').text();
    $('#'+fila_id).attr('title',nombre_cliente);
    var cli_id = $('#'+fila_id+' select option:selected').val();
    var label_cliente = "<label class='cursor_cruz'>"+cli_id+"</label>";
    $('#'+fila_id+' select').replaceWith(label_cliente);
  }
}

function actualizarDeudaCliente(fila_id, evento)
{
  if(evento == 13)
  {
    var hiv_id = fila_id.split("_")[2];
    var valor_nuevo = $('#'+fila_id+' select').val();
    ajax('accion=actualizarDeudaCliente&hiv_id='+hiv_id+"&valor_nuevo="+valor_nuevo, false, actualizarDeudaClienteAjax, false);
    return true;
  }
  else
    return false;
}

function actualizarDeudaClienteAjax(jsonDeuda)
{
  var obj_deuda = eval("("+jsonDeuda+")");
  if(obj_deuda.valor_deuda != 0)
  {
    $("#cli_span_debe_"+obj_deuda.hiv_id).children().remove();
    $("#cli_span_debe_"+obj_deuda.hiv_id).html("<img id='cli_img_debe_"+obj_deuda.hiv_id+"' class='imagen_deuda' src='../imagenes/deuda.gif' title='Debe "+obj_deuda.valor_deuda+" de otros dias'/>");
  }
  else
    $("#cli_span_debe_"+obj_deuda.hiv_id).children().remove();
}

function editableTotal(fila_id,editable)
{
  if(editable)
  {
    var hiv_total = $('#'+fila_id).children().text();
    var input_total = "<input type='text' maxlength='6' class='ancho_100p verdana letra_9' onBlur='if(actualizarValor(\""+fila_id+"\",\"hiv_total\",13)){ editableTotal(\""+fila_id+"\",false);}' onKeypress='if(actualizarValor(\""+fila_id+"\",\"hiv_total\",event.keyCode)){ editableTotal(\""+fila_id+"\",false);}' value='"+hiv_total+"'/>";
    $('#'+fila_id).children().replaceWith(input_total);
    $('#'+fila_id).children().select();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editableTotal(\"'+fila_id+'\",true);');
    var hiv_total = parseInt($('#'+fila_id).children().val());
    if(hiv_total == "" || isNaN(hiv_total))
      hiv_total = "0";
    var label_total = "<label class='cursor_cruz'>"+hiv_total+"</label>";
    $('#'+fila_id).children().replaceWith(label_total);
  }
}

function editableDeudaReal(fila_id,editable)
{
  if(editable)
  {
    var hiv_deuda_real = $('#'+fila_id).children().text();
    var input_deuda_real = "<input type='text' maxlength='6' class='ancho_100p verdana letra_9' onBlur='if(actualizarValor(\""+fila_id+"\",\"hiv_deuda_real\",13)){ editableDeudaReal(\""+fila_id+"\",false);}' onKeypress='if(actualizarValor(\""+fila_id+"\",\"hiv_deuda_real\",event.keyCode)){ editableDeudaReal(\""+fila_id+"\",false);}' value='"+hiv_deuda_real+"'/>";
    $('#'+fila_id).children().replaceWith(input_deuda_real);
    $('#'+fila_id).children().select();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editableDeudaReal(\"'+fila_id+'\",true);');
    var hiv_deuda_real = parseInt($('#'+fila_id).children().val());
    if(hiv_deuda_real == "" || isNaN(hiv_deuda_real))
      hiv_deuda_real = "0";
    var label_deuda_real = "<label class='cursor_cruz'>"+hiv_deuda_real+"</label>";
    $('#'+fila_id).children().replaceWith(label_deuda_real);
  }
}

function editableHoraInicio(fila_id,editable)
{
  if(editable)
  {
    var hiv_hora = $('#'+fila_id).children().text();
    var selects_hora_inicio = "<input type='text' maxlength='5' class='ancho_100p verdana letra_9 ' onBlur='if(actualizarInicio(\""+fila_id+"\",13)){ editableHoraInicio(\""+fila_id+"\",false);}' onKeypress='if(actualizarInicio(\""+fila_id+"\",event.keyCode)){ editableHoraInicio(\""+fila_id+"\",false);}' value='"+hiv_hora+"'/>";
    $('#'+fila_id).children().replaceWith(selects_hora_inicio);
    $('#'+fila_id).children().select();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editableHoraInicio(\"'+fila_id+'\",true);');
    var label_hora = "<label class='cursor_cruz'>"+$('#'+fila_id).children().val()+"</label>";
    $('#'+fila_id).children().replaceWith(label_hora);
  }
}

function actualizarInicio(fila_id, evento)
{
  if(evento == 13)
  {
  ///^\d{1,2}[\.\:]\d{1,2}$/;//#.# ó #:# viejita
    var filtro = filtro = /^(([1][0-2]?)|[1-9])[\.\:]([0-5]?[0-9])$/;//formato de hora valida
    if (filtro.test($('#'+fila_id).children().val()))
    {
      var arreglo_id = fila_id.split("_");
      var hiv_id = arreglo_id[(arreglo_id.length - 1)];
      var valor_nuevo = $('#'+fila_id).children().val().replace(".", ":");
      ajax('accion=actualizarInicio&hiv_id='+hiv_id+"&valor_nuevo="+valor_nuevo, false, actualizarTiemposYTotalAjax, false);
      return true;
    }
    else
    {
      $('#'+fila_id).children().addClass('letra_roja');
      return false;
    }
  }
  else
    return false;
}

function editableDuracion(fila_id,editable)
{
  if(editable)
  {
    var hiv_dus_minutos = $('#hidden_'+fila_id).val();
    var selects_duracion = "<select id='"+fila_id+"' class='verdana letra_9 ancho_100p' onchange='if(actualizarDuracion(\""+fila_id+"\",13)){ editableDuracion(\""+fila_id+"\",false);}' onBlur='if(actualizarDuracion(\""+fila_id+"\",13)){ editableDuracion(\""+fila_id+"\",false);}'>";
    selects_duracion += options_duracion;
    selects_duracion += "</select>";
    $('#'+fila_id).children("label").replaceWith(selects_duracion);
    $('#'+fila_id).children("label").removeAttr('selected', 'selected');
    $('#'+fila_id+" select option[value='"+hiv_dus_minutos+"']").attr('selected', 'selected');
    $('#'+fila_id).children("select").focus();
  }
  else
  {
    var duracion = $('#'+fila_id+" select option:selected").text();
    var label_duracion = "<label class='cursor_cruz'>"+duracion+"</label>";
    $('#hidden_'+fila_id).val($('#'+fila_id).children("select").val());
    $('#'+fila_id).children("select").replaceWith(label_duracion);
  }
}

function actualizarDuracion(fila_id, evento)
{
  if(evento == 13)
  {
    var arreglo_id = fila_id.split("_");
    var hiv_id = arreglo_id[(arreglo_id.length - 1)];
    var valor_nuevo = $('#'+fila_id).children("select").val();
    ajax('accion=actualizarDuracion&hiv_id='+hiv_id+"&valor_nuevo="+valor_nuevo, false, actualizarTiemposYTotalAjax, false);
    return true;
  }
  else
    return false;
}

function actualizarTiemposYTotalAjax(json_horas)
{
  //alert(json_horas);
  var obj_horas = eval("("+json_horas+")");
  //se utilizan los LABELS porque el llamado ajax es asincrono y cuando llega
  //la respuesta, ya los inputs se han transformado en labels
  //se espera que siempre sea asi
  $("#hiv_hora_"+obj_horas.hiv_id).children().text(obj_horas.hiv_hora);
  $("#hiv_dus_minutos_"+obj_horas.hiv_id).children().text(obj_horas.dus_texto);
  $("#hiv_hora_termina_"+obj_horas.hiv_id).children().text(obj_horas.hiv_hora_termina);
  $("#hiv_total_"+obj_horas.hiv_id).children().text(obj_horas.hiv_total);
  return true;
}

function editableObservacion(fila_id,editable)
{
  if(editable)
  {
    var hiv_observacion = $('#'+fila_id).children().text();
    var input_observacion = "<input type='text' class='ancho_100p verdana letra_9' onBlur='if(actualizarValor(\""+fila_id+"\",\"hiv_observacion\",13)){ editableObservacion(\""+fila_id+"\",false);}' onKeypress='if(actualizarValor(\""+fila_id+"\",\"hiv_observacion\",event.keyCode)){ editableObservacion(\""+fila_id+"\",false);}' value='"+hiv_observacion+"'/>";
    $('#'+fila_id).children().replaceWith(input_observacion);
    $('#'+fila_id).children().focus();
    $('#'+fila_id).removeAttr("onclick");
  }
  else
  {
    $('#'+fila_id).attr('onClick','editableObservacion(\"'+fila_id+'\",true);');
    var hiv_observacion = $('#'+fila_id).children().val();
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
    console.log("actualizado!");
  else
    console.log("no se actualizo ningun valor de la fila");
}

function asignarListenersColores()
{
  var arreglo_filas = document.getElementsByName('fila_historico');
  for(var x = 0; x < arreglo_filas.length ; x++)
  {
    //el ID tiene la forma ==> hiv_fila_<#>
    var arregloIdFila = arreglo_filas[x].id.split("_");
    var consecutivo = arregloIdFila[2];
    $("#hiv_color_"+consecutivo).attachColorPicker();
      $("#hiv_color_"+consecutivo).change(
        function() {cambiarColorFila(this);}
      );
  }
}

function cambiarColorFila(elemento)
{
  //el ID tiene la forma ==> hiv_fila_<#>
  var arregloIdFila = elemento.id.split("_");
  var consecutivo = arregloIdFila[2];
  var color = $("#"+elemento.id).getValue();
  actualizarCampoColor(consecutivo, color);
}

function actualizarCampoColor(id, color_fila)
{
  ajax("accion=actualizarCampoColor&hiv_id="+id+"&hiv_color_fila="+color_fila, null, actualizarCampoColorAjax, null);
}

function actualizarCampoColorAjax(json_color)
{
  if(json_color)
  {
    var obj_color = eval("("+json_color+")");
    $("#hiv_fila_"+obj_color.id).attr('style','{background:'+obj_color.color+';}');
    var color = " ";
    if(obj_color.color != 'null')
      color = obj_color.color;
    $("#hiv_color_oculto_"+obj_color.id).html(color);
    actualizarOrdenamiento();
    //$("#tbl_historial").trigger("update");
  }
  else
    console.log("No se acualizo ningun color");
}

function actualizarEstadoPago(id_fila, ultimo_clic)
{
  var hiv_pago = $('#hiv_chk_pago_'+id_fila).attr('checked');
  var hiv_es_tiempo_gratis = $('#hiv_chk_gratis_'+id_fila).attr('checked');

  if($("#hiv_deuda_real_"+id_fila).children("label").html() != "0")
  {
    if(confirm("Esto coloca la deuda en CERO. ¿esta seguro?"))
      ajax("accion=actualizarEstadoPago&id_fila="+id_fila+"&hiv_pago="+hiv_pago+"&hiv_es_tiempo_gratis="+hiv_es_tiempo_gratis+"&ultimo_clic="+ultimo_clic, null, actualizarEstadoPagoAjax, null);
    else
    {
      $('#hiv_chk_pago_'+id_fila).removeAttr('checked');
      $('#hiv_chk_gratis_'+id_fila).removeAttr('checked');
    }
  }
  else
    ajax("accion=actualizarEstadoPago&id_fila="+id_fila+"&hiv_pago="+hiv_pago+"&hiv_es_tiempo_gratis="+hiv_es_tiempo_gratis+"&ultimo_clic="+ultimo_clic, null, actualizarEstadoPagoAjax, null);
}

function actualizarEstadoPagoAjax(json_estado_pago)
{
  var obj_estado_pago = eval("("+json_estado_pago+")");
  if(obj_estado_pago.hiv_id)
  {
    //se coloca en ceros el campo deuda
    $("#hiv_deuda_real_"+obj_estado_pago.hiv_id).children("label").html("0");
    if(obj_estado_pago.ultimo_clic == "pago")
    {
      if($('#hiv_chk_pago_'+obj_estado_pago.hiv_id).attr('checked'))
      {
        $("#hiv_pago_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
        $("#hiv_pago_"+obj_estado_pago.hiv_id).addClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
        $("#hiv_chk_gratis_"+obj_estado_pago.hiv_id).removeAttr("checked");
      }
      else
      {
        $("#hiv_pago_"+obj_estado_pago.hiv_id).addClass("celda_debe");
        $("#hiv_pago_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
      }
    }
    else if(obj_estado_pago.ultimo_clic == "gratis")
    {
      if($('#hiv_chk_gratis_'+obj_estado_pago.hiv_id).attr('checked'))
      {
        $("#hiv_pago_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
        $("#hiv_pago_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).addClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
        $("#hiv_chk_pago_"+obj_estado_pago.hiv_id).removeAttr("checked");
      }
      else
      {
        $("#hiv_pago_"+obj_estado_pago.hiv_id).addClass("celda_debe");
        $("#hiv_pago_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_pago");
        $("#hiv_gratis_"+obj_estado_pago.hiv_id).removeClass("celda_debe");
      }
    }
  }
  else
    console.log('Error actualizando estado del pago');
}

function eliminarFila(id)
{
  ajax("accion=eliminarFila&id="+id, mensajeConfirmar, eliminarFilaAjax, null);
}

function eliminarFilaAjax(id_eliminado)
{
  if(id_eliminado)
  {
    $("#"+id_eliminado).remove();
    actualizarOrdenamiento();
    //$("#tbl_historial").trigger("update");    
  }
}

/**********************************
******* ACCIONES HISTORIAL  *******
***********************************/


function agregarFilaHistorial(hiv_ser_id,ser_tipo)
{
  var fecha_actual = new Date();
  var anno_actual = fecha_actual.getFullYear();
  var mes_actual = fecha_actual.getMonth() + 1;
  if(mes_actual < 10)
    mes_actual = "0"+mes_actual;
  var dia_actual = fecha_actual.getDate();

  var arregloHoraInicio = obtenerArregloHoraInicio();
  var hiv_dus_minutos = "";
  var hiv_total = "";
//   if(ser_tipo == "servicio")
//     hiv_dus_minutos = $("#hiv_dus_minutos").val();
//   if(ser_tipo == "producto")
//     hiv_total = $("#hiv_total").val();

  //se guarda la fecha del producto vendido deacuerdo a
  //la fecha de la contabilidad abierta actualmente
  var hiv_fecha = anno_actual+"-"+mes_actual+"-"+dia_actual;
  if($("#fecha_contabilidad").val() != hiv_fecha)
    hiv_fecha = $("#fecha_contabilidad").val();

  ajax("accion=agregarFilaHistorial&hiv_ser_id="+hiv_ser_id+
        "&hiv_ser_tipo="+ser_tipo+
        "&hiv_hora="+arregloHoraInicio[0]+
        "&hiv_minuto="+arregloHoraInicio[1]+
        "&hiv_meridiano="+arregloHoraInicio[2]+
        "&hiv_dus_minutos="+hiv_dus_minutos+
        "&hiv_total="+hiv_total+
        "&hiv_fecha="+hiv_fecha, null, agregarFilaHistorialAjax, null);
}

function agregarFilaHistorialAjax(fila)
{
  if(fila)
  {
    $("#historial_ventas").append(fila);
    asignarListenersColores();
    actualizarOrdenamiento();
  }
  else
    console.log('Error al registrar el servicio');
}

function obtenerArregloHoraInicio()
{
  var fecha = new Date();
  var hora = fecha.getHours();
  var minutos = fecha.getMinutes();
  var minuto_digito_derecha = "0";
  var minuto_digito_izquierda = "0"; //no siempre existe

  if(minutos > 9)
  {
    minuto_digito_izquierda = (""+minutos)[0];
    minuto_digito_derecha = (""+minutos)[1];
  }
  else
    minuto_digito_derecha = (""+minutos)[0];

  var minutos_redondeados = "99";
  if(parseInt(minuto_digito_derecha) < 5)
    minutos_redondeados = minuto_digito_izquierda+"5";
  else
  {
    var nuevo_digito_izquierda = parseInt(minuto_digito_izquierda)+1;
    if(nuevo_digito_izquierda < 6)
      minutos_redondeados = nuevo_digito_izquierda+"0";
    else
    {
      minutos_redondeados = "00";
      hora++;
    }
  }
  var meridiano = "99";
  if(hora < 12)
    meridiano = "am";
  else
  {
    meridiano = "pm";
    if(hora != 12)
      hora = hora - 12;
  }
  if(hora == 0)
    hora = 12;

  var arregloHora = new Array(3);
  arregloHora[0] = hora;
  arregloHora[1] = parseInt(minutos_redondeados);
  arregloHora[2] = meridiano;
  return arregloHora;
}


function actualizarHistorialVentas()
{
  ajax("accion=actualizarHistorialVentas", null, actualizarHistorialVentasAjax, null);
}

function actualizarHistorialVentasAjax(info_servicios)
{
  $("#historial_ventas").children().remove();
  $("#historial_ventas").html(info_servicios);
  asignarListenersColores();
  actualizarOrdenamiento();
}


/**********************************
******* ACCIONES TIMERS     *******
***********************************/
/*
var arreglo_CronoID;
var arreglo_CronoEjecutandose;
var arreglo_bandera_incrementa;
var arreglo_segundos = new Array(5);
var arreglo_minutos = new Array(5);
var arreglo_horas = new Array(5);

function obtenerInfoTimers()
{
  ajax("accion=obtenerInfoTimers", null, obtenerInfoTimersAjax, null);
}

function obtenerInfoTimersAjax(json_timers)
{
  var obj_timers = eval('('+json_timers+')');

  arreglo_bandera_incrementa = new Array(obj_timers.length);
  arreglo_CronoEjecutandose = new Array(obj_timers.length);
  arreglo_CronoID = new Array(obj_timers.length);
  arreglo_segundos = new Array(obj_timers.length);
  arreglo_minutos = new Array(obj_timers.length);
  arreglo_horas = new Array(obj_timers.length);

  for(var x = 0; x < obj_timers.length; x++)
  {
    var duracion_timer = obj_timers[x].tim_dus_minutos.split(":");
    $('#tim_duracion_horas_'+x).val(duracion_timer[0]);
    $('#tim_duracion_minutos_'+x).val(duracion_timer[1]);
    //inicializo arreglos
    arreglo_bandera_incrementa[x] = (obj_timers[x].tim_es_incremental == 1) ? true : false;
    arreglo_CronoEjecutandose[x] = (obj_timers[x].tim_esta_ejecutando == 1) ? true : false;
    if(arreglo_bandera_incrementa[x] == true) //si es incremental (tiempo libre)
    {
      var tiempo_inicia = obj_timers[x].tim_inicia;
      var tiempo_lleva = obj_timers[x].tim_lleva;
      if(tiempo_lleva.length >= 9) //error porque tiempo es mas de 99 horas!
        arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = '99';
      else
      {
        arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = 0;
        var arreglo_tiempo_lleva = tiempo_lleva.split(":");
        arreglo_segundos[x] = parseInt(arreglo_tiempo_lleva[2]);
        arreglo_minutos[x] = parseInt(arreglo_tiempo_lleva[1]);
        arreglo_horas[x] = parseInt(arreglo_tiempo_lleva[0]);
      }
    }
    else //si es decremental (tiempo prefijado)
    {
      var tiempo_finaliza = obj_timers[x].tim_finaliza;
      var tiempo_falta = obj_timers[x].tim_falta;
      if(tiempo_falta.length >= 9)//error porq ya es negativo, se paso!
        arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = '99';
      else
      {
        arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = 0;
        var arreglo_tiempo_falta = tiempo_falta.split(":");
        arreglo_segundos[x] = parseInt(arreglo_tiempo_falta[2]);
        arreglo_minutos[x] = parseInt(arreglo_tiempo_falta[1]);
        arreglo_horas[x] = parseInt(arreglo_tiempo_falta[0]);
      }
    }
  }
  for(var y = 0; y < obj_timers.length; y++)
  {
    if(arreglo_CronoEjecutandose[y] == true)//si se esta ejecutando
      IniciarCrono(y);
    else//si no esta ejecutandose
    {

    }
  }
}

function DetenerCrono (pos)
{
  //detiene hilos
  if(arreglo_CronoEjecutandose[pos])
    clearTimeout(arreglo_CronoID[pos]);
  arreglo_CronoEjecutandose[pos] = false;
  arreglo_CronoID[pos] = null;
  //colocar boton y accion de play
  $('#img_play_pause_'+pos).attr('src', '../imagenes/play.jpg');
  $('#btn_play_pause_'+pos).attr('onClick', 'IniciarCrono('+pos+');');
}

function InicializarCrono (pos)
{
  DetenerCrono(pos);
  arreglo_horas[pos] = parseInt($('#tim_duracion_horas_'+pos).val());
  arreglo_minutos[pos] = parseInt($('#tim_duracion_minutos_'+pos).val());
  arreglo_segundos[pos] = 0;
  var horas = (arreglo_horas[pos] < 10) ? "0" + arreglo_horas[pos] : arreglo_horas[pos];
  var minutos = (arreglo_minutos[pos] < 10) ? "0" + arreglo_minutos[pos] : arreglo_minutos[pos];
  var segundos = (arreglo_segundos[pos] < 10) ? "0" + arreglo_segundos[pos] : arreglo_segundos[pos];
  //inicializa interfaz
  $('#lbl_timer_'+pos).html(horas+":"+minutos+":"+segundos);
}

function ejecutarCrono (pos)
{
  var parar = false;
  if(arreglo_bandera_incrementa[pos] == 1)
  {
    //si marca 99:99:99 se detiene
    if( arreglo_horas[pos] == 99 && arreglo_minutos[pos] == 99 && arreglo_segundos[pos] == 99)
    {
      alert('se pasaron ole! turu truu!');
      DetenerCrono(pos);
      parar = true;
    }
    else
    {
      //incrementa el crono
      arreglo_segundos[pos]++;
      if ( arreglo_segundos[pos] > 59 )
      {
        arreglo_segundos[pos] = 0;
        arreglo_minutos[pos]++;
        if ( arreglo_minutos[pos] > 59 )
        {
          arreglo_minutos[pos] = 0;
          arreglo_horas[pos]++;
        }
      }
    }
  }
  else
  {
    if( parseInt(arreglo_horas[pos]) == 99)
    {
      alert('se acabo! turu truu!');
      DetenerCrono(pos);
      parar = true;
    }
    else
    {
      //decrementa
      arreglo_segundos[pos]--;
      if ( arreglo_segundos[pos] < 0 )
      {
        arreglo_segundos[pos] = 59;
        arreglo_minutos[pos]--;
        if ( arreglo_minutos[pos] < 0 )
        {
          arreglo_minutos[pos] = 59;
          arreglo_horas[pos]--;
          if ( arreglo_horas[pos] < 0 )
            arreglo_horas[pos] = 99;
        }
      }
    }
  }

  //configura la salida
  var ValorCrono = "";
  ValorCrono = (arreglo_horas[pos] < 10) ? arreglo_horas[pos] : arreglo_horas[pos];
  ValorCrono += (arreglo_minutos[pos] < 10) ? ":0" + parseInt(arreglo_minutos[pos]) : ":" + arreglo_minutos[pos];
  ValorCrono += (arreglo_segundos[pos] < 10) ? ":0" + parseInt(arreglo_segundos[pos]) : ":" + arreglo_segundos[pos];
  $('#lbl_timer_'+pos).html(ValorCrono);
  if(parar)
    return false;
  arreglo_CronoID[pos] = setTimeout("ejecutarCrono("+pos+")", 1000);
  arreglo_CronoEjecutandose[pos] = true;
  return true;
}

function IniciarCrono (pos)
{
  ajax("accion=IniciarCrono&id="+pos+"&", null, obtenerInfoTimersAjax, null);
  ejecutarCrono(pos);
  //colocar boton y accion de pause
  $('#img_play_pause_'+pos).attr('src', '../imagenes/pause.jpg');
  $('#btn_play_pause_'+pos).attr('onClick', 'DetenerCrono('+pos+');');
}*/