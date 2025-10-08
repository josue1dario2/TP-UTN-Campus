#include <iostream>
#include <sstream>
#include "EstadoMateria.h"

using namespace std;

EstadoMateria::EstadoMateria()
{
    _idEstado = 0;
    _idAlumno = 0;
    _plan = 0;
    _idPlanMateria = 0;
    _estadoMateriaAlumno = 0;
    _ultimaNota = 0;
}

EstadoMateria::EstadoMateria(int idEstado, int idAlumno, int plan, int idPlanMateria, int estadoMateriaAlumno, int ultimaNota)
{
    setIdEstado(idEstado);
    setIdAlumno(idAlumno);
    setPlan(plan);
    setIdPlanMateria(idPlanMateria);
    setEstadoMateriaAlumno(estadoMateriaAlumno);
    setUltimaNota(ultimaNota);
}

void EstadoMateria::setIdEstado(int idEstado)
{
    _idEstado = (idEstado >= 0 ? idEstado : 0);
}

void EstadoMateria::setIdAlumno(int idAlumno)
{
    _idAlumno = (idAlumno >= 0 ? idAlumno : 0);
}

void EstadoMateria::setPlan(int plan)
{
    _plan = (plan >= 0 ? plan : 0);
}

void EstadoMateria::setIdPlanMateria(int idPlanMateria)
{
    _idPlanMateria = (idPlanMateria >= 0 ? idPlanMateria : 0);
}

void EstadoMateria::setEstadoMateriaAlumno(int estadoMateriaAlumno)
{
    if (estadoMateriaAlumno >= 0 && estadoMateriaAlumno <= 3)
        _estadoMateriaAlumno = estadoMateriaAlumno;
    else
        _estadoMateriaAlumno = 0;
}

void EstadoMateria::setUltimaNota(int ultimaNota)
{
    if (ultimaNota >= 0 && ultimaNota <= 10)
        _ultimaNota = ultimaNota;
    else
        _ultimaNota = 0;
}

int EstadoMateria::getIdEstado() const { return _idEstado; }
int EstadoMateria::getIdAlumno() const { return _idAlumno; }
int EstadoMateria::getPlan() const { return _plan; }
int EstadoMateria::getIdPlanMateria() const { return _idPlanMateria; }
int EstadoMateria::getEstadoMateriaAlumno() const { return _estadoMateriaAlumno; }
int EstadoMateria::getUltimaNota() const { return _ultimaNota; }

void EstadoMateria::cargar()
{
    int estado, nota;
    cout << "Ingrese idEstado: ";
    cin >> _idEstado;
    cout << "Ingrese idAlumno: ";
    cin >> _idAlumno;
    cout << "Ingrese plan: ";
    cin >> _plan;
    cout << "Ingrese idPlanMateria: ";
    cin >> _idPlanMateria;
    cout << "Ingrese estadoMateriaAlumno (0=Sin cursar, 1=Cursando, 2=Regular, 3=Aprobada): ";
    cin >> estado;
    setEstadoMateriaAlumno(estado);
    cout << "Ingrese ultima nota (0-10): ";
    cin >> nota;
    setUltimaNota(nota);
}

void EstadoMateria::mostrar() const
{
    cout << toString() << endl;
}

string EstadoMateria::toString() const
{
    stringstream ss;
    ss << "ID Estado: " << _idEstado
       << " | ID Alumno: " << _idAlumno
       << " | Plan: " << _plan
       << " | ID PlanMateria: " << _idPlanMateria
       << " | EstadoMateriaAlumno: " << _estadoMateriaAlumno
       << " | UltimaNota: " << _ultimaNota;
    return ss.str();
}
