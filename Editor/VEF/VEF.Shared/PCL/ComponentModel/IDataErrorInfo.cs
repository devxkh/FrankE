using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.ComponentModel
{
    // Zusammenfassung:
    //     Stellt Funktionen für die Unterstützung benutzerdefinierter Fehlerinformationen
    //     bereit, an die eine Benutzeroberfläche gebunden werden kann.
    public interface IDataErrorInfo
    {
        // Zusammenfassung:
        //     Ruft eine Fehlermeldung ab, die den Fehler in diesem Objekt angibt.
        //
        // Rückgabewerte:
        //     Eine Fehlermeldung, die den Fehler in diesem Objekt angibt.Der Standardwert
        //     ist eine leere Zeichenfolge ("").
        string Error { get; }

        // Zusammenfassung:
        //     Ruft die Fehlermeldung für die Eigenschaft mit dem angegebenen Namen ab.
        //
        // Parameter:
        //   columnName:
        //     Der Name der Eigenschaft, deren Fehlermeldung abgerufen werden soll.
        //
        // Rückgabewerte:
        //     Die Fehlermeldung für die Eigenschaft.Der Standardwert ist eine leere Zeichenfolge
        //     ("").
        string this[string columnName] { get; }
    }
}
