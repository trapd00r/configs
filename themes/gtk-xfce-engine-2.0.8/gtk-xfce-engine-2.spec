Summary: 	Port of xfce engine to GTK+-2.0
Name: 		gtk-xfce-engine
Version: 	2.0.8
Release: 	1
License:	GPL
URL: 		http://www.xfce.org/
Source0: 	%{name}-%{version}.tar.gz
Group: 		User Interface/Desktops
BuildRoot: 	%{_tmppath}/%{name}-root
Requires:	gtk2
Requires:	glib2
BuildRequires: 	gtk2-devel >= 2.0.0
BuildRequires: 	glib2-devel >= 2.0.0

%description
A port of Xfce engine to GTK+-2.0.

%prep
%setup -q

%build
%configure
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_libdir}/*
%{_datadir}/*

