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

#pragma once

#include <cppuhelper/implbase4.hxx>
#include <rtl/ustring.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XServiceName.hpp>
#include <com/sun/star/sheet/XAddIn.hpp>
#include <com/sun/star/sheet/FormattedResult.hpp>
#include <uk/co/busydoingnothing/funcs/XFuncs.hpp>

namespace com::sun::star::uno
{
class XComponentContext;
}

namespace uk::co::busydoingnothing::funcs
{
typedef cppu::WeakImplHelper4<css::lang::XServiceInfo, css::lang::XServiceName, css::sheet::XAddIn,
                              XFuncs>
    AddInBase;

class AddIn : public AddInBase
{
public:
    // XServiceInfo
    rtl::OUString SAL_CALL getImplementationName() override;
    sal_Bool SAL_CALL supportsService(rtl::OUString const& serviceName) override;
    css::uno::Sequence<rtl::OUString> SAL_CALL getSupportedServiceNames() override;

    // XServiceName
    rtl::OUString SAL_CALL getServiceName() override;

    // XLocalizable
    void SAL_CALL setLocale(const css::lang::Locale& eLocale) override;
    css::lang::Locale SAL_CALL getLocale() override;

    // XAddIn
    rtl::OUString SAL_CALL getProgrammaticFuntionName(const rtl::OUString& aDisplayName) override;
    rtl::OUString SAL_CALL getDisplayFunctionName(const rtl::OUString& aProgrammaticName) override;
    rtl::OUString SAL_CALL getFunctionDescription(const rtl::OUString& aProgrammaticName) override;
    rtl::OUString SAL_CALL getDisplayArgumentName(const rtl::OUString& aProgrammaticFunctionName,
                                                  sal_Int32 nArgument) override;
    rtl::OUString SAL_CALL getArgumentDescription(const rtl::OUString& aProgrammaticFunctionName,
                                                  sal_Int32 nArgument) override;
    rtl::OUString SAL_CALL
    getProgrammaticCategoryName(const rtl::OUString& aProgrammaticFunctionName) override;
    rtl::OUString SAL_CALL
    getDisplayCategoryName(const rtl::OUString& aProgrammaticFunctionName) override;

    // XFuncs
    double SAL_CALL doubleValue(double nValue) override;
    css::sheet::FormattedResult getDate() override;
    css::sheet::FormattedResult getMatrix() override;

    static rtl::OUString getImplementationNameStatic();
    static css::uno::Sequence<rtl::OUString> getSupportedServiceNamesStatic();
    static css::uno::Reference<css::uno::XInterface>
    create(const css::uno::Reference<css::uno::XComponentContext>& xContext);

private:
    AddIn();

    css::lang::Locale m_aLocale;
};
}
