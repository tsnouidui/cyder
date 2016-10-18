model {{modelName}}
  "Block that exchanges a vector of real values with CYMDIST"
  extends Modelica.Blocks.Interfaces.DiscreteBlock(
    startTime=0,
    firstTrigger(fixed=true, start=false));
///////////// THE CODE BELOW HAS BEEN AUTOMATICALLY GENERATED //////////////   
  {%- for dict_item in scalarVariables %}
  {%- if (dict_item["causality"])== "parameter" %}
  parameter {{dict_item["vartype"]}} {{dict_item["name"]}}(unit="{{dict_item["unit"]}}") = {{dict_item["start"]}}
    "{{dict_item["description"]}}";
  {%- elif (dict_item["causality"])== "input" %}
  Modelica.Blocks.Interfaces.RealInput {{dict_item["name"]}}(start={{dict_item["start"]}}, unit="{{dict_item["unit"]}}")
    "{{dict_item["description"]}}"{{dict_item["annotation"]}};
  {%- elif (dict_item["causality"])== "output" %}
  Modelica.Blocks.Interfaces.RealOutput {{dict_item["name"]}} (unit="{{dict_item["unit"]}}")
    "{{dict_item["description"]}}"{{dict_item["annotation"]}};
  {%- endif -%}
  {% endfor %}
 
protected   
  parameter String moduleName
    "Name of the python module that contains the function";
  parameter String functionName=moduleName "Name of the python function";
  parameter Integer nDblPar = {{parameterVariableNames|length}} 
    "Number of double parameter values to sent to CYMDIST";
  parameter Integer nDblInp(min=1) = {{inputVariableNames|length}} 
    "Number of double input values to sent to CYMDIST";
  parameter Integer nDblOut(min=1) = {{outputVariableNames|length}}  
    "Number of double output values to receive from CYMDIST";
  parameter Integer flaDblInp[nDblInp] = zeros(nDblInp)
    "Flag for double values (0: use current value, 
    1: use average over interval, 2: use integral over interval)";
  
  {% set comma = joiner(",") -%}  
  Real uR[nDblInp]={
  {%- for row in inputVariableNames -%}
  {{comma()}}
  {{row}}
  {%- endfor %} 
  }"Variables used to collect values to be sent to CYMDIST";
  
  {% set comma = joiner(",") -%} 
  Real yR[nDblOut]={
  {%- for row in outputVariableNames -%}
  {{comma()}}
  {{row}}
  {%- endfor %} 
  }"Variable used to collect values received from CYMDIST";
  
  Real uRInt[nDblInp] "Value of integral";
  Real uRIntPre[nDblInp] "Value of integral at previous sampling instance";
  Real dblInpVal[nDblInp] "Value to be sent to CYMDIST";
  
  {% set comma = joiner(",") -%}   
  parameter String dblInpNam[nDblInp] = {
  {%- for row in inputVariableNames -%}
  {{comma()}}
  "{{row}}"
  {%- endfor %} 
  }"Input variables names to be sent to CYMDIST";
  
  {% set comma = joiner(",") -%} 
  parameter String dblOutNam[nDblOut] = {
  {%- for row in outputVariableNames -%}
  {{comma()}}
  "{{row}}"
  {%- endfor %} 
  }"Output variables names to be received from CYMDIST";
  
  {% set comma = joiner(",") -%} 
  parameter String dblParNam[nDblPar] = {
  {%- for row in parameterVariableNames -%}
  {{comma()}}
  "{{row}}"
  {%- endfor %}
  }"Parameter variables names to be sent to CYMDIST";

  {% set comma = joiner(",") -%} 
  parameter Real dblParVal[nDblPar] = {
  {%- for row in parameterVariableValues -%}
  {{comma()}}
  {{row}}
  {%- endfor %}
  }"Parameter variables values to be sent to CYMDIST";

///////////// THE CODE ABOVE HAS BEEN AUTOMATICALLY GENERATED //////////////  
  
initial equation 
  dblInpVal    =  pre(uR);
  uRInt    =  zeros(nDblInp);
  uRIntPre =  zeros(nDblInp);
  for i in 1:nDblInp loop
    assert(flaDblInp[i]>=0 and flaDblInp[i]<=2,
      "Parameter flaDblInp out of range for " + String(i) + "-th component.");
  end for;
  // The assignment of yR avoids the warning
  // "initial conditions for variables of type Real are not fully specified".
  // At startTime, the sampleTrigger is true and hence this value will
  // be overwritten.

  yR = zeros(nDblOut);
equation 
  for i in 1:nDblInp loop
    der(uRInt[i]) = if (flaDblInp[i] > 0) then uR[i] else 0;
  end for;
   
  when {sampleTrigger} then
    // Compute value that will be sent to CYMDIST
    for i in 1:nDblInp loop
      if (flaDblInp[i] == 0) then
        // Send the current value.
        dblInpVal[i] = pre(uR[i]); 
      else
        // Integral over the sampling interval
        dblInpVal[i] = uRInt[i] - pre(uRIntPre[i]);
        if (flaDblInp[i] == 1) then
          // Average value over the sampling interval
          dblInpVal[i] =  dblInpVal[i]/samplePeriod;  
        end if;
      end if;
    end for;
      
    // Exchange data
    yR = Buildings.Utilities.IO.Python27.Functions.cymdist(
      moduleName=moduleName,
      functionName=functionName,
      nDblInp=nDblInp,
      dblInpNam=dblInpNam,
      dblInpVal=dblInpVal,
      nDblOut=nDblOut,
      dblOutNam=dblOutNam,
      nDblPar=nDblPar,
      dblParNam=dblParNam,
      dblParVal=dblParVal);
  // Store current value of integral
  uRIntPre= uRInt;
  end when;    
end {{modelName}};
