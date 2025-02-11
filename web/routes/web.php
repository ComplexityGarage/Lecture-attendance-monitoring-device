<?php

use App\Http\Controllers\Visitors\ResetVisitsController;
use App\Http\Controllers\ProfileController;
use App\Models\Visit;
use Illuminate\Support\Facades\Route;
use Inertia\Inertia;

Route::get('/', function () {
    return redirect()->route('dashboard');
});

Route::get('/dashboard', function () {
    return Inertia::render('Dashboard', [
        'visitsOnServer' => Visit::query()->orderByDesc('id')->get()
    ]);
})->middleware(['auth', 'verified'])->name('dashboard');

Route::middleware('auth')->group(function () {
    Route::get('/profile', [ProfileController::class, 'edit'])->name('profile.edit');
    Route::patch('/profile', [ProfileController::class, 'update'])->name('profile.update');
    Route::delete('/profile', [ProfileController::class, 'destroy'])->name('profile.destroy');

    Route::post('/visitors/reset', ResetVisitsController::class)->name('visitors.reset');
});

require __DIR__ . '/auth.php';
