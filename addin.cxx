// Funcs – A test extension for LibreOffice to add some Calc functions
// Copyright (C) 2026  Neil Roberts
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "addin.hxx"

#include <com/sun/star/util/NumberFormat.hpp>

using namespace rtl;

namespace uk::co::busydoingnothing::funcs
{
AddIn::AddIn() {}

rtl::OUString SAL_CALL AddIn::getImplementationName() { return getImplementationNameStatic(); }

sal_Bool SAL_CALL AddIn::supportsService(OUString const& serviceName)
{
    for (const OUString& sService : getSupportedServiceNamesStatic())
    {
        if (sService == serviceName)
            return true;
    }

    return false;
}

css::uno::Sequence<OUString> SAL_CALL AddIn::getSupportedServiceNames()
{
    return getSupportedServiceNamesStatic();
}

OUString AddIn::getImplementationNameStatic()
{
    return OUString("uk.co.busydoingnothing.funcs.AddIn");
}

css::uno::Sequence<OUString> AddIn::getSupportedServiceNamesStatic()
{
    css::uno::Sequence<OUString> names(2);
    names[0] = OUString("com.sun.star.sheet.AddIn");
    names[1] = OUString("uk.co.busydoingnothing.funcs.Funcs");
    return names;
}

rtl::OUString SAL_CALL AddIn::getServiceName()
{
    return OUString("uk.co.busydoingnothing.funcs.Funcs");
}

void SAL_CALL AddIn::setLocale(const css::lang::Locale& eLocale) { m_aLocale = eLocale; }

css::lang::Locale SAL_CALL AddIn::getLocale() { return m_aLocale; }

rtl::OUString SAL_CALL AddIn::getProgrammaticFuntionName(const rtl::OUString& aDisplayName)
{
    return aDisplayName;
}

rtl::OUString SAL_CALL AddIn::getDisplayFunctionName(const rtl::OUString& aProgrammaticName)
{
    return aProgrammaticName;
}

rtl::OUString SAL_CALL AddIn::getFunctionDescription(const rtl::OUString& aProgrammaticName)
{
    if (aProgrammaticName == "doubleValue")
        return OUString("Doubles the given value");
    else
        return OUString("Returns a date");
}

rtl::OUString SAL_CALL AddIn::getDisplayArgumentName(const rtl::OUString& aProgrammaticFunctionName,
                                                     sal_Int32 nArgument)
{
    return OUString("value");
}

rtl::OUString SAL_CALL AddIn::getArgumentDescription(const rtl::OUString& aProgrammaticFunctionName,
                                                     sal_Int32 nArgument)
{
    return OUString("the value to double");
}

rtl::OUString SAL_CALL
AddIn::getProgrammaticCategoryName(const rtl::OUString& aProgrammaticFunctionName)
{
    return OUString("Mathematical");
}

rtl::OUString SAL_CALL AddIn::getDisplayCategoryName(const rtl::OUString& aProgrammaticFunctionName)
{
    return OUString("Mathematical");
}

double SAL_CALL AddIn::doubleValue(double nValue) { return nValue * 2.0; }

css::sheet::FormattedResult SAL_CALL AddIn::getDate()
{
    css::uno::Sequence<css::uno::Sequence<sal_Int16>> formats(1);
    formats[0].realloc(1);
    formats[0][0] = css::util::NumberFormat::DATE;
    css::uno::Sequence<css::uno::Sequence<OUString>> codes(1);
    codes[0].realloc(1);
    codes[0][0] = OUString("YYYY-MM-DD");

    css::sheet::FormattedResult aResult = {
        css::uno::Any(sal_Int32(-1476)),
        std::move(formats),
        std::move(codes),
    };

    return aResult;
}

css::sheet::FormattedResult SAL_CALL AddIn::getMatrix()
{
    css::uno::Sequence<css::uno::Sequence<sal_Int16>> formats(1);
    formats[0].realloc(2);
    formats[0][0] = css::util::NumberFormat::DATE;
    formats[0][1] = css::util::NumberFormat::PERCENT;
    css::uno::Sequence<css::uno::Sequence<OUString>> codes(1);
    codes[0].realloc(2);
    codes[0][0] = OUString("YYYY-MM-DD");

    css::uno::Sequence<css::uno::Sequence<css::uno::Any>> values(1);
    values[0].realloc(2);
    values[0][0] = css::uno::Any(sal_Int32(-1476));
    values[0][1] = css::uno::Any(sal_Int32(42));

    css::sheet::FormattedResult aResult = {
        css::uno::Any(values),
        std::move(formats),
        std::move(codes),
    };

    return aResult;
}

css::uno::Reference<css::uno::XInterface>
AddIn::create(const css::uno::Reference<css::uno::XComponentContext>& xContext)
{
    css::uno::Reference<AddIn> xAddIn = new AddIn;

    return xAddIn;
}
}
