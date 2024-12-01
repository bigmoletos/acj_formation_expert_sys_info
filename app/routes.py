@bp.route('/logout')
@login_required
def logout():
    """Route pour la déconnexion"""
    logout_user()
    flash('Vous avez été déconnecté')
    return redirect(url_for('main.login'))
