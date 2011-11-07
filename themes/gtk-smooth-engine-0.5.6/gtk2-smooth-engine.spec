Summary: 	The Smooth engine for GTK+-2.0
Name: 		gtk-smooth-engine
Version: 	0.5.6
Release: 	1
License:	LGPL
URL: 		http://sourceforge.net/projects/smooth-engine/
Source0: 	%{name}-%{version}.tar.gz
Group: 		User Interface/Desktops
BuildRoot: 	%{_tmppath}/%{name}-root
Requires:	gtk2
Requires:	glib2
Requires:	gtk+
Requires:	glib
BuildRequires: 	gtk2-devel >= 2.0.0
BuildRequires: 	glib2-devel >= 2.0.0
BuildRequires:	gtk+-devel >= 1.2.9
BuildRequires:	glib >= 1.2.9

%description
The Smooth engine for GTK+-2.0

%prep
%setup -q

%build
%configure --enable-gtk-1
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_libdir}/*

